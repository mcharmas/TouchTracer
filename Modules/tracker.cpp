#include "tracker.h"

Tracker::Tracker(QObject *parent) :
    QObject(parent)
{
    frameTouches = new QList<QVector<Touch>*>();
    framesToStore = 10;
    usedIds = 0;
    maxTravelDistance = 25;
    movementFilter = 0;
    currentTouches = new QMap<long, Touch>();
    server = new TuioServer();
}

Tracker::~Tracker()
{
    destroyAllFrames();
    delete frameTouches;
}

void Tracker::destroyAllFrames()
{
    if(frameTouches->size())
    {
        for(QList<QVector<Touch>*>::iterator it = frameTouches->begin(); it!=frameTouches->end(); it++)
        {
            destroyFrameTouches((*it));
        }
        frameTouches->clear();
    }

}

void Tracker::drawTouches(QVector<Touch> * t, Mat & mat)
{
    for(QVector<Touch>::iterator it = t->begin();it != t->end();it++){
        Touch & t = (*it);
        t.drawMiddle(mat);
        t.drawId(mat);
    }
}

void Tracker::cleanFrameList()
{
    if(frameTouches->size() == framesToStore){
        QVector<Touch> *t = frameTouches->last();
        frameTouches->removeLast();
        destroyFrameTouches(t);
    }
}

void Tracker::pushNewTouches(vector<vector<Point> >& touches, Mat& mat)
{
    if(!touches.size())
    {
//        qDebug() << "No touches in this frame.";
        destroyAllFrames();
        notifyTUIO(NULL);
        return;
    }

    QVector<Touch> *t = new QVector<Touch>();
    for(vector<vector<Point> >::iterator it=touches.begin(); it!=touches.end(); it++)
    {
        t->append(Touch(*it));
    }

    identifyFingers(t);
    cleanFrameList();
    drawTouches(t, mat);
    notifyTUIO(t);
    frameTouches->prepend(t);
}

void Tracker::destroyFrameTouches(QVector<Touch> *touches)
{
    delete touches;
}

void Tracker::identifyFingers(QVector<Touch>* touches)
{
    if(!touches)
        return;

    if(frameTouches->size()==0)
    {
        QVector<Touch>::iterator it = touches->begin();
        for(;it!=touches->end();it++)
        {
            (*it).setId(usedIds++);
        }
        return;
    }

    QMap<int,bool> takenIds;
    for(QVector<Touch>::iterator it = touches->begin();it!=touches->end();it++)
    {
        Touch &t = (*it);
        long id = findId(t, *frameTouches, takenIds);

        Touch *t_old = findTouch(id);
        if(t_old!=NULL && t.distance(*t_old) < movementFilter )
        {
            t = *t_old;
            t.setMoved(false);
        }
        t.setId(id);
    }
}

Touch* Tracker::findTouch(long id)
{
    QVector<Touch> *t = frameTouches->first();
    for(QVector<Touch>::iterator it = t->begin(); it!=t->end(); it++)
    {
        if ((*it).getId() == id)
        {
            return &(*it);
        }
    }
    return NULL;
}

void Tracker::notifyTUIO(QVector<Touch> *touches)
{

    server->initFrame(TuioTime::getSessionTime());
    if(!touches)
    {
        for(QMap<long,TuioCursor*>::iterator it=tuioObjects.begin();it!=tuioObjects.end(); it++)
        {
            server->removeTuioCursor(*it);
        }
        tuioObjects.clear();
        server->commitFrame();
        return;
    }

    QList<long> keysToRemove(tuioObjects.keys());
    for(QVector<Touch>::iterator it = touches->begin(); it!=touches->end(); it++)
    {
        Touch &t = (*it);
        if(tuioObjects.find(t.getId())==tuioObjects.end())
        {
            tuioObjects[t.getId()] = server->addTuioCursor(t.getTuioX(), t.getTuioY());
        }
        else
        {
            if(t.hasMoved())
            {
                server->updateTuioCursor(tuioObjects[t.getId()], t.getTuioX(), t.getTuioY());
            }
            keysToRemove.removeOne(t.getId());
        }
    }

    for(QList<long>::iterator it = keysToRemove.begin(); it!=keysToRemove.end(); it++)
    {
        TuioCursor *tc = tuioObjects[(*it)];
        server->removeTuioCursor(tc);
        tuioObjects.remove((*it));
    }
    server->commitFrame();
}

long Tracker::findId(const Touch &t, QList<QVector<Touch> *> list, QMap<int,bool>& takenIds)
{
    multiset<QPair<double,int> > distances;
    for(QList<QVector<Touch> *>::iterator it1 = list.begin(); it1!=list.end(); it1++)
    {
        for(QVector<Touch>::iterator it = (*it1)->begin(); it != (*it1)->end(); it++ )
        {
            distances.insert(QPair<double,int>(t.distance(*it), (*it).getId()));
        }
    }

    int k = 5;
    int i=0;
    QMap<int, double> candidates;
    for(multiset<QPair<double,int> >::iterator it=distances.begin(); it!=distances.end() && i < k; it++, i++)
    {
        if((*it).first > maxTravelDistance)
            break;

        if(candidates.find((*it).second)==candidates.end())
        {
            candidates.insert((*it).second, 1);
        }
        else
        {
            candidates[(*it).second]++;
        }
    }

    if(candidates.size()==0)
    {
        return usedIds++;
    }

    set<QPair<int, int> >sortedCand;
    for(QMap<int, double>::iterator it = candidates.begin(); it!=candidates.end();it++)
        sortedCand.insert(QPair<int,int>(it.key(), it.value()));

    int assignedId = -1;
    for(set<QPair<int, int> >::iterator it=sortedCand.begin(); it!=sortedCand.end(); it++)
    {
        int id = (*it).first;
        if(takenIds.find(id)==takenIds.end())
        {
            assignedId = id;
            takenIds[id] = true;
            break;
        }
    }

    if(assignedId == -1)
    {
        assignedId = usedIds++;
    }

    return assignedId;
}
