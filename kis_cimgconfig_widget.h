/*
 * This file is part of Krita
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
 *
 * Ported from the CImg Gimp plugin by Victor Stinner and David Tschumperlé.
 */
#ifndef _KIS_CIMGCONFIG_WIDGET_
#define _KIS_CIMGCONFIG_WIDGET_

#include "ui_wdg_cimg.h"
#include "filter/kis_filter.h"
#include "kis_config_widget.h"

class WdgCImg : public QWidget, public Ui::WdgCImg
{
    Q_OBJECT

public:
    WdgCImg(QWidget *parent) : QWidget(parent) {
        setupUi(this);
    }
};

class KisCImgconfigWidget : public KisConfigWidget
{

    Q_OBJECT

public:

    KisCImgconfigWidget(QWidget * parent = 0, Qt::WFlags f = 0);
    virtual ~KisCImgconfigWidget() {}

public:

    KisPropertiesConfiguration* configuration() const;
    void setConfiguration(const KisPropertiesConfiguration* config);

private:
    WdgCImg * m_page;

};

#endif // _KIS_CIMGCONFIG_WIDGET_
