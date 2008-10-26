/*
 * This file is part of the KDE project
 *
 * Copyright (c) 2005 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef _KIS_CIMG_FILTER_H_
#define _KIS_CIMG_FILTER_H_

#include "filter/kis_filter.h"
#include "kis_config_widget.h"
#include <filter/kis_filter_configuration.h>
#include <kis_selection.h>
#include <kis_paint_device.h>
#include <kis_processing_information.h>
#include "CImg.h"

class KisCImgFilterConfiguration : public KisFilterConfiguration
{

public:

    using KisFilterConfiguration::fromXML;

    KisCImgFilterConfiguration();
    virtual QString toString();
    virtual void fromXML(const QString & s);

public:

    qint32 nb_iter;    // Number of smoothing iterations
    double dt;         // Time step
    double dlength;    // Integration step
    double dtheta;     // Angular step (in degrees)
    double sigma;      // Structure tensor blurring
    double power1;     // Diffusion limiter along isophote
    double power2;     // Diffusion limiter along gradient
    double gauss_prec; //  Precision of the gaussian function
    bool onormalize; // Output image normalization (in [0,255])
    bool linear;     // Use linear interpolation for integration ?
};


class KisCImgFilter : public KisFilter
{
public:
    KisCImgFilter();
public:

    using KisFilter::process;

    void process(KisConstProcessingInformation src,
                 KisProcessingInformation dst,
                 const QSize& size,
                 const KisFilterConfiguration* config,
                 KoUpdater* progressUpdater
                ) const;
    static inline KoID id() {
        return KoID("cimg", i18n("Image Restoration (cimg-based)"));
    }

public:
    virtual KisConfigWidget * createConfigurationWidget(QWidget* parent, KisPaintDeviceSP dev, const KisImageSP image = 0) const;
    virtual KisFilterConfiguration * configuration(QWidget*);
    virtual KisPropertiesConfiguration * configuration() {
        return new KisCImgFilterConfiguration();
    }
private:

    bool process();

    // Compute smoothed structure tensor field G
    void compute_smoothed_tensor();

    // Compute normalized tensor field sqrt(T) in G
    void compute_normalized_tensor();

    // Compute LIC's along different angle projections a_\alpha
    void compute_LIC(int &counter);
    void compute_LIC_back_forward(int x, int y);
    void compute_W(float cost, float sint);

    // Average all the LIC's
    void compute_average_LIC();

    // Prepare data
    bool prepare();
    bool prepare_restore();
    bool prepare_inpaint();
    bool prepare_resize();
    bool prepare_visuflow();

    // Check arguments
    bool check_args();

    // Clean up memory (CImg data) to save memory
    void cleanup();

private:
    unsigned int nb_iter; // Number of smoothing iterations
    float dt;       // Time step
    float dlength; // Integration step
    float dtheta; // Angular step (in degrees)
    float sigma;  // Structure tensor blurring
    float power1; // Diffusion limiter along isophote
    float power2; // Diffusion limiter along gradient
    float gauss_prec; //  Precision of the gaussian function
    bool onormalize; // Output image normalization (in [0,255])
    bool linear; // Use linear interpolation for integration


    // internal use
    bool restore;
    bool inpaint;
    bool resize;
    const char* visuflow;
    cimg_library::CImg<> dest, sum, W;
    cimg_library::CImg<> img, img0, flow, G;
    cimg_library::CImgl<> eigen;
    cimg_library::CImg<unsigned char> mask;

};

#endif
