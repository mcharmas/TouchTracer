#ifndef TRACKER_H
#define TRACKER_H

#include <QObject>
#include <set>
#include <QMap>
#include <QPair>
#include <QList>
#include <QVector>
#include <QDebug>
#include <cv.h>
#include <highgui.h>

#include "touch.h"

using namespace std;
using namespace cv;

/**
 * @brief Class used to track contours.
 *
 * Methods of this class assigns id to touches on the basis of previous frames using kNN algorithm.
*/
class Tracker : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent QObject parent
    */
    explicit Tracker(QObject *parent = 0);

    /**
     * @brief Clean up.
    */
    ~Tracker();

    /**
     * @brief Method used to add frame contours information to Tracker.
     *
     * When touches param i empty it cleans up information of all frames.
     * All frame's touches are stored in QList<QVector<Touch>*> *frameTouches.
     * Only the last framesToStore frames are stored in frameTouches.
     *
     * How it works:
     * - Creates QVector of touches on the basis of OpenCV contours
     * - calls identifyFingers() method with created collection
     * - if frameTouches is full (has size()==frameToStore) the last frame is removed
     * - all touches contours and ids are drawn
     * - touches are added do frameTouches collection
     *
     * @param touches OpenCV contours of filtered touches on the surface
     * @param mat used to draw contours and ids
    */
    void pushNewTouches(vector<vector<Point> >& touches, Mat& mat);

protected:


    /**
     * @brief Deletes vector of touches.
     * @param touches
    */
    void destroyFrameTouches(QVector<Touch>* touches);

    /**
     * @brief Used to remove all data from frameTouches.
    */
    void destroyAllFrames();

    /**
     * @brief Function used to identify fingers.
     *
     * How it works:
     * - if no information about previous frames it assignes sequent ids to all touches
     * - else, it calls findId() for each finger
     * @param touches collection of touches to be identified
    */
    void identifyFingers(QVector<Touch> *touches);

    /**
     * @brief Implements kNN algorithm and calculates id for given touch on the
     *        basis of previous frames touches and used ids in this frame.
     *
     * When the best id is already taken the next from the list is assigned.
     * When the closest finger to touch is futher than maxTravelDistance (class field)
     * the new id is assigned.
     *
     * @param t touch to assign id
     * @param list list of all previous frames touches
     * @param takenIds map of taken ids
    */
    long findId(const Touch& t, QList<QVector<Touch>*> list, QMap<int, bool>& takenIds);

    int framesToStore; /**< Number of history frames hold in frameTouches. */
    int usedIds; /**< Already used ids. */
    QList<QVector<Touch>*> *frameTouches; /**< History of frame touches. */
    double maxTravelDistance; /**< Biggest distance the finger can travel between frames (in pixels). */

};

#endif // TRACKER_H
