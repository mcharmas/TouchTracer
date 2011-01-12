#ifndef MODULEFILTERS_H
#define MODULEFILTERS_H
#include "module.h"
#include "modulefilterssettings.h"
#include <cv.h>
#include <highgui.h>
#include <QObject>

using namespace cv;

/**
 * @brief Class implementing image filters.
 *
 * Now supports: blur, gain
 * @class ModuleFilters modulefilters.h "Modules/modulefilters.h"
*/
class ModuleFilters : public Module
{
    Q_OBJECT
public:
    /**
     * @brief Contructor.
     * @param parent QObject parent
    */
    explicit ModuleFilters(QObject *parent = 0);

    /**
     * @brief Clean up.
    */
    virtual ~ModuleFilters();

    /**
     * @brief Processes current frame.
     *
     * Applies filters if necessary.
     * Blur is applied only when window size > 1.
     * Gain is applied only when factor > 1;
     * @param mat to be processed
    */
    void process(Mat &mat);

    AbstractSettingsWidget* getSettingsWidget() { return settings; }

    QString getName() { return "Filters module"; }

public slots:
    /**
     * @brief Changes blur window size.
     * @param x window size
    */
    void changeBlur(int x);

    /**
     * @brief Changes blur window size in unsharp mask filter.
     * @param x window size
    */
    void changeSharp(int x);

    /**
     * @brief Changes gain factor.
     *
     * Gain factor is counted by dividing int value by 100 in order to get factor double value.
     * If value has to be greater than 100 to change.
     * @param x gain value <100;*> divided by 100 to get factor
    */
    void changeGain(int x);

    /**
     * @brief Changes image flip
     * @param i probably not used at all
    */
    void changeFlip(int i);


private:
    ModuleFiltersSettings *settings; /**< Settings widget. */
    int blurValue; /**< Blur window size. */
    int sharpValue; /**< Sharp Blur window size. */
    double gain; /**< Gain factor. */
    bool vFlip, hFlip; /**< Flips. */

};

#endif // MODULEFILTERS_H
