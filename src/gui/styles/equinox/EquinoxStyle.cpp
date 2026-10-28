/*
 *  Copyright (C) 2026 Equinox Team
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 */

#include "EquinoxStyle.h"

#include <QDialog>
#include <QFile>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

EquinoxStyle::EquinoxStyle()
    : BaseStyle()
{
}

QPalette EquinoxStyle::standardPalette() const
{
    auto palette = BaseStyle::standardPalette();

    // Vercel Monochromatic Pure Black Palette
    palette.setColor(QPalette::Active, QPalette::Window, QRgb(0x000000));
    palette.setColor(QPalette::Inactive, QPalette::Window, QRgb(0x000000));
    palette.setColor(QPalette::Disabled, QPalette::Window, QRgb(0x09090B));

    palette.setColor(QPalette::Active, QPalette::WindowText, QRgb(0xFFFFFF));
    palette.setColor(QPalette::Inactive, QPalette::WindowText, QRgb(0xE4E4E7));
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QRgb(0x52525B));

    palette.setColor(QPalette::Active, QPalette::Text, QRgb(0xFFFFFF));
    palette.setColor(QPalette::Inactive, QPalette::Text, QRgb(0xE4E4E7));
    palette.setColor(QPalette::Disabled, QPalette::Text, QRgb(0x52525B));

    palette.setColor(QPalette::Active, QPalette::PlaceholderText, QRgb(0x71717A));
    palette.setColor(QPalette::Inactive, QPalette::PlaceholderText, QRgb(0x71717A));
    palette.setColor(QPalette::Disabled, QPalette::PlaceholderText, QRgb(0x3F3F46));

    palette.setColor(QPalette::Active, QPalette::BrightText, QRgb(0xFFFFFF));
    palette.setColor(QPalette::Inactive, QPalette::BrightText, QRgb(0xFFFFFF));
    palette.setColor(QPalette::Disabled, QPalette::BrightText, QRgb(0x52525B));

    // Input / View background surfaces
    palette.setColor(QPalette::Active, QPalette::Base, QRgb(0x0A0A0A));
    palette.setColor(QPalette::Inactive, QPalette::Base, QRgb(0x0A0A0A));
    palette.setColor(QPalette::Disabled, QPalette::Base, QRgb(0x121212));

    palette.setColor(QPalette::Active, QPalette::AlternateBase, QRgb(0x111111));
    palette.setColor(QPalette::Inactive, QPalette::AlternateBase, QRgb(0x111111));
    palette.setColor(QPalette::Disabled, QPalette::AlternateBase, QRgb(0x18181B));

    // ToolTips
    palette.setColor(QPalette::All, QPalette::ToolTipBase, QRgb(0x121212));
    palette.setColor(QPalette::All, QPalette::ToolTipText, QRgb(0xFFFFFF));

    // Buttons
    palette.setColor(QPalette::Active, QPalette::Button, QRgb(0x0A0A0A));
    palette.setColor(QPalette::Inactive, QPalette::Button, QRgb(0x0A0A0A));
    palette.setColor(QPalette::Disabled, QPalette::Button, QRgb(0x121212));

    palette.setColor(QPalette::Active, QPalette::ButtonText, QRgb(0xFFFFFF));
    palette.setColor(QPalette::Inactive, QPalette::ButtonText, QRgb(0xE4E4E7));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QRgb(0x52525B));

    // High-contrast inverted Vercel selection
    palette.setColor(QPalette::Active, QPalette::Highlight, QRgb(0xFFFFFF));
    palette.setColor(QPalette::Inactive, QPalette::Highlight, QRgb(0x27272A));
    palette.setColor(QPalette::Disabled, QPalette::Highlight, QRgb(0x18181B));

    palette.setColor(QPalette::Active, QPalette::HighlightedText, QRgb(0x000000));
    palette.setColor(QPalette::Inactive, QPalette::HighlightedText, QRgb(0xFFFFFF));
    palette.setColor(QPalette::Disabled, QPalette::HighlightedText, QRgb(0x52525B));

    // Borders & Dividers
    palette.setColor(QPalette::All, QPalette::Light, QRgb(0x262626));
    palette.setColor(QPalette::All, QPalette::Midlight, QRgb(0x1F1F1F));
    palette.setColor(QPalette::All, QPalette::Mid, QRgb(0x262626));
    palette.setColor(QPalette::All, QPalette::Dark, QRgb(0x18181B));
    palette.setColor(QPalette::All, QPalette::Shadow, QRgb(0x000000));

    // Links
    palette.setColor(QPalette::All, QPalette::Link, QRgb(0xFFFFFF));
    palette.setColor(QPalette::Disabled, QPalette::Link, QRgb(0x71717A));
    palette.setColor(QPalette::All, QPalette::LinkVisited, QRgb(0xA1A1AA));
    palette.setColor(QPalette::Disabled, QPalette::LinkVisited, QRgb(0x71717A));

    return palette;
}

int EquinoxStyle::pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const
{
    switch (metric) {
    case PM_DefaultFrameWidth:
        return 1;
    case PM_ButtonMargin:
        return 6;
    case PM_LayoutHorizontalSpacing:
        return 8;
    case PM_LayoutVerticalSpacing:
        return 8;
    case PM_TabBarTabHSpace:
        return 16;
    case PM_TabBarTabVSpace:
        return 6;
    case PM_ToolBarItemSpacing:
        return 6;
    case PM_ScrollBarExtent:
        return 8;
    default:
        return BaseStyle::pixelMetric(metric, option, widget);
    }
}

QString EquinoxStyle::getAppStyleSheet() const
{
    QFile extStylesheetFile(QStringLiteral(":/styles/equinox/equinox.qss"));
    if (extStylesheetFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return extStylesheetFile.readAll();
    }
    qWarning("Failed to load Equinox theme stylesheet.");
    return {};
}

void EquinoxStyle::polish(QWidget* widget)
{
    if (qobject_cast<QMainWindow*>(widget) || qobject_cast<QDialog*>(widget) || qobject_cast<QMenuBar*>(widget)
        || qobject_cast<QToolBar*>(widget)) {
        auto palette = widget->palette();
        palette.setColor(QPalette::Active, QPalette::Window, QRgb(0x000000));
        palette.setColor(QPalette::Inactive, QPalette::Window, QRgb(0x000000));
        widget->setPalette(palette);
    }
    BaseStyle::polish(widget);
}
