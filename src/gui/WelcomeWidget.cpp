/*
 *  Copyright (C) 2012 Felix Geyer <debfx@fobos.de>
 *  Copyright (C) 2020 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "WelcomeWidget.h"
#include "ui_WelcomeWidget.h"
#include <QKeyEvent>

#include "config-keepassx.h"
#include "core/Config.h"
#include "gui/Icons.h"

WelcomeWidget::WelcomeWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::WelcomeWidget())
{
    m_ui->setupUi(this);

    m_ui->welcomeLabel->setText(QStringLiteral("Equinox"));
    QFont welcomeLabelFont = m_ui->welcomeLabel->font();
    welcomeLabelFont.setFamily(QStringLiteral("Space Grotesk"));
    welcomeLabelFont.setBold(true);
    welcomeLabelFont.setPointSize(welcomeLabelFont.pointSize() + 8);
    m_ui->welcomeLabel->setFont(welcomeLabelFont);
    m_ui->welcomeLabel->setStyleSheet("color: #FFFFFF; letter-spacing: -0.5px; margin-bottom: 2px;");

    m_ui->startLabel->setText(tr("Cofre de credenciais moderno, seguro e soberano."));
    m_ui->startLabel->setStyleSheet("color: #71717A; font-size: 13px; margin-bottom: 16px;");

    m_ui->iconLabel->setPixmap(icons()->applicationIcon().pixmap(48));
    m_ui->buttonNewDatabase->setIcon(icons()->icon("document-new"));
    m_ui->buttonNewDatabase->setStyleSheet("QPushButton { background-color: #FFFFFF; color: #000000; border: 1px solid #FFFFFF; border-radius: 6px; font-weight: 600; padding: 8px 16px; font-size: 13px; } QPushButton:hover { background-color: #E4E4E7; }");

    m_ui->buttonOpenDatabase->setIcon(icons()->icon("document-open"));
    m_ui->buttonOpenDatabase->setStyleSheet("QPushButton { background-color: #0A0A0A; color: #FFFFFF; border: 1px solid #27272A; border-radius: 6px; font-weight: 500; padding: 8px 16px; font-size: 13px; } QPushButton:hover { background-color: #18181B; border: 1px solid #3F3F46; }");

    m_ui->buttonImport->setIcon(icons()->icon("document-import"));
    m_ui->buttonImport->setStyleSheet("QPushButton { background-color: #0A0A0A; color: #FFFFFF; border: 1px solid #27272A; border-radius: 6px; font-weight: 500; padding: 8px 16px; font-size: 13px; } QPushButton:hover { background-color: #18181B; border: 1px solid #3F3F46; }");

    m_ui->recentListWidget->setStyleSheet("QListWidget { background-color: #0A0A0A; border: 1px solid #27272A; border-radius: 8px; padding: 4px; } QListWidget::item { padding: 8px 12px; border-radius: 4px; color: #FFFFFF; } QListWidget::item:hover { background-color: #121212; } QListWidget::item:selected { background-color: #18181B; color: #FFFFFF; }");

    refreshLastDatabases();

    connect(m_ui->buttonNewDatabase, SIGNAL(clicked()), SIGNAL(newDatabase()));
    connect(m_ui->buttonOpenDatabase, SIGNAL(clicked()), SIGNAL(openDatabase()));
    connect(m_ui->buttonImport, SIGNAL(clicked()), SIGNAL(importFile()));
    connect(m_ui->recentListWidget,
            SIGNAL(itemActivated(QListWidgetItem*)),
            this,
            SLOT(openDatabaseFromFile(QListWidgetItem*)));
}

WelcomeWidget::~WelcomeWidget() = default;

void WelcomeWidget::openDatabaseFromFile(QListWidgetItem* item)
{
    if (!item || item->text().isEmpty()) {
        return;
    }
    emit openDatabaseFile(item->text());
}

void WelcomeWidget::removeFromLastDatabases(QListWidgetItem* item)
{
    if (!item || item->text().isEmpty()) {
        return;
    }

    if (config()->get(Config::RememberLastDatabases).toBool()) {
        QStringList lastDatabases = config()->get(Config::LastDatabases).toStringList();
        lastDatabases.removeOne(item->text());
        config()->set(Config::LastDatabases, lastDatabases);
    }
    refreshLastDatabases();
}

void WelcomeWidget::refreshLastDatabases()
{
    m_ui->recentListWidget->clear();
    const QStringList lastDatabases = config()->get(Config::LastDatabases).toStringList();
    for (const QString& database : lastDatabases) {
        auto itm = new QListWidgetItem;
        itm->setText(database);
        m_ui->recentListWidget->addItem(itm);
    }

    bool recent_visibility = (m_ui->recentListWidget->count() > 0);
    m_ui->startLabel->setVisible(!recent_visibility);
    m_ui->recentListWidget->setVisible(recent_visibility);
    m_ui->recentLabel->setVisible(recent_visibility);
}

void WelcomeWidget::keyPressEvent(QKeyEvent* event)
{
    if (m_ui->recentListWidget->hasFocus()) {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            openDatabaseFromFile(m_ui->recentListWidget->currentItem());
        } else if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) {
            removeFromLastDatabases(m_ui->recentListWidget->currentItem());
        }
    }

    QWidget::keyPressEvent(event);
}

void WelcomeWidget::showEvent(QShowEvent* event)
{
    refreshLastDatabases();
    QWidget::showEvent(event);
}
