/*
 *  Copyright (C) 2026 Equinox Team
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 */

#ifndef EQUINOX_STYLE_H
#define EQUINOX_STYLE_H

#include "gui/styles/base/BaseStyle.h"

class EquinoxStyle : public BaseStyle
{
    Q_OBJECT

public:
    EquinoxStyle();
    QPalette standardPalette() const override;

    using BaseStyle::polish;
    void polish(QWidget* widget) override;
    int pixelMetric(PixelMetric metric, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const override;

protected:
    QString getAppStyleSheet() const override;
};

#endif // EQUINOX_STYLE_H
