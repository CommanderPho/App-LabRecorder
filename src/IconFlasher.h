#ifndef ICONFLASHER_H
#define ICONFLASHER_H

#include <QObject>
#include <QTimer>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QMainWindow>

class IconFlasher : public QObject {
    Q_OBJECT

public:
    explicit IconFlasher(QMainWindow *window, QObject *parent = nullptr)
        : QObject(parent), m_window(window), m_state(false) {
        
        // Cache the original icon
        m_originalIcon = window->windowIcon();
        if (m_originalIcon.isNull()) {
            // Fallback if no icon is set: use a standard system icon or transparent
            m_originalIcon = window->style()->standardIcon(QStyle::SP_ComputerIcon);
        }

        // Pre-render the "Recording" icon (Original + Red Dot)
        m_recordingIcon = createRecordingIcon(m_originalIcon);

        // Setup Timer
        m_timer = new QTimer(this);
        m_timer->setInterval(800); // 800ms flash interval
        connect(m_timer, &QTimer::timeout, this, &IconFlasher::toggleIcon);
    }

    void start() {
        if (!m_timer->isActive()) {
            m_timer->start();
            m_state = true;
            updateWindowIcon();
        }
    }

    void stop() {
        m_timer->stop();
        // Always restore the original clean icon when stopping
        m_window->setWindowIcon(m_originalIcon);
    }

private slots:
    void toggleIcon() {
        m_state = !m_state;
        updateWindowIcon();
    }

private:
    void updateWindowIcon() {
        if (m_state) {
            m_window->setWindowIcon(m_recordingIcon);
        } else {
            m_window->setWindowIcon(m_originalIcon);
        }
    }

    QIcon createRecordingIcon(const QIcon &baseIcon) {
        // Get the highest resolution pixmap available (e.g., 64x64 or higher)
        QPixmap pixmap = baseIcon.pixmap(64, 64);
        
        // Setup Painter
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // Define Dot Size (e.g., 30% of icon size)
        int size = pixmap.width() * 0.35;
        int margin = 2; 
        
        // Draw Red Circle in bottom-right corner
        QRect rect(pixmap.width() - size - margin, 
                   pixmap.height() - size - margin, 
                   size, size);
        
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen); // No outline
        painter.drawEllipse(rect);
        
        return QIcon(pixmap);
    }

    QMainWindow *m_window;
    QTimer *m_timer;
    QIcon m_originalIcon;
    QIcon m_recordingIcon;
    bool m_state;
};

#endif // ICONFLASHER_H