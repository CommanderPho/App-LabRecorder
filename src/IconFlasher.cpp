#include "IconFlasher.h"
#include <QStyle>
#include <QPixmap>
#include <QPainter>
#include <QApplication>
#include <QRadialGradient>

IconFlasher::IconFlasher(QWidget *window, int flashInterval, double dotSizeRatio,
                         const QColor &dotColor, DotPosition dotPosition, QObject *parent)
    : QObject(parent), m_window(window), m_state(false), m_dotSizeRatio(dotSizeRatio),
      m_dotColor(dotColor), m_dotPosition(dotPosition) {
    
    // Cache the original icon
    m_originalIcon = window->windowIcon();
    if (m_originalIcon.isNull()) {
        // Fallback if no icon is set: use a standard system icon
        QStyle *style = window->style();
        if (!style) {
            style = QApplication::style();
        }
        if (style) {
            m_originalIcon = style->standardIcon(QStyle::SP_ComputerIcon);
        }
    }

    // Pre-render the "Recording" icon (Original + Red Dot) with multiple sizes
    m_recordingIcon = createRecordingIcon(m_originalIcon);

    // Setup Timer
    m_timer = new QTimer(this);
    m_timer->setInterval(flashInterval);
    connect(m_timer, &QTimer::timeout, this, &IconFlasher::toggleIcon);
}

void IconFlasher::start() {
    if (!m_timer->isActive()) {
        m_timer->start();
        m_state = true;
        updateWindowIcon();
    }
}

void IconFlasher::stop() {
    m_timer->stop();
    // Always restore the original clean icon when stopping
    m_window->setWindowIcon(m_originalIcon);
}

void IconFlasher::setFlashInterval(int interval) {
    m_timer->setInterval(interval);
}

void IconFlasher::toggleIcon() {
    m_state = !m_state;
    updateWindowIcon();
}

void IconFlasher::updateWindowIcon() {
    if (m_state) {
        m_window->setWindowIcon(m_recordingIcon);
    } else {
        m_window->setWindowIcon(m_originalIcon);
    }
}

QIcon IconFlasher::createRecordingIcon(const QIcon &baseIcon) {
    QIcon recordingIcon;
    
    // Standard icon sizes for cross-platform compatibility
    // These sizes ensure proper rendering at different DPIs and contexts
    const QList<int> iconSizes = {16, 32, 48, 64, 128, 256};
    
    for (int size : iconSizes) {
        // Get pixmap at the requested size
        QPixmap pixmap = baseIcon.pixmap(size, size);
        
        // If base icon doesn't have this size, create a scaled version
        if (pixmap.isNull() || pixmap.size().isEmpty()) {
            // Try to get a larger size and scale down, or create a blank pixmap
            QPixmap largerPixmap = baseIcon.pixmap(size * 2, size * 2);
            if (!largerPixmap.isNull()) {
                pixmap = largerPixmap.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            } else {
                // Create a blank pixmap as fallback
                pixmap = QPixmap(size, size);
                pixmap.fill(Qt::transparent);
            }
        }
        
        // Ensure pixmap is exactly the requested size
        if (pixmap.size() != QSize(size, size)) {
            pixmap = pixmap.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        
        // Setup Painter with high-quality rendering
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        
        // Calculate dot size and position
        int dotSize = static_cast<int>(size * m_dotSizeRatio);
        int margin = qMax(1, size / 32); // Proportional margin, minimum 1 pixel
        
        QRect dotRect;
        switch (m_dotPosition) {
            case TopRight:
                dotRect = QRect(size - dotSize - margin, margin, dotSize, dotSize);
                break;
            case TopLeft:
                dotRect = QRect(margin, margin, dotSize, dotSize);
                break;
            case BottomLeft:
                dotRect = QRect(margin, size - dotSize - margin, dotSize, dotSize);
                break;
            case BottomRight:
            default:
                dotRect = QRect(size - dotSize - margin, size - dotSize - margin, dotSize, dotSize);
                break;
        }
        
        // Draw red circle with subtle shadow for better visibility
        // Shadow (darker, slightly offset)
        QRect shadowRect = dotRect.translated(1, 1);
        painter.setBrush(QColor(m_dotColor.red() / 2, m_dotColor.green() / 2, m_dotColor.blue() / 2, 180));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(shadowRect);
        
        // Main dot
        painter.setBrush(m_dotColor);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(dotRect);
        
        // Add a subtle highlight for depth
        if (dotSize > 8) {
            QRect highlightRect = dotRect.adjusted(1, 1, -1, -1);
            QRadialGradient gradient(highlightRect.center(), highlightRect.width() / 2);
            gradient.setColorAt(0, QColor(255, 255, 255, 100));
            gradient.setColorAt(1, QColor(255, 255, 255, 0));
            painter.setBrush(gradient);
            painter.drawEllipse(highlightRect);
        }
        
        painter.end();
        
        // Add this size to the icon
        recordingIcon.addPixmap(pixmap);
    }
    
    return recordingIcon;
}

