#ifndef ICONFLASHER_H
#define ICONFLASHER_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QIcon>
#include <QColor>

class QStyle;

/**
 * @brief The IconFlasher class provides a cross-platform flashing recording indicator
 * 
 * This class adds an animated red dot indicator to a window's icon when recording is active.
 * It works by toggling between the original icon and a modified icon with a red dot overlay.
 * The implementation generates multiple icon sizes for proper display across different
 * platforms and DPI settings.
 */
class IconFlasher : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Enumeration for dot position on the icon
     */
    enum DotPosition {
        BottomRight,  ///< Dot in bottom-right corner (default)
        TopRight,     ///< Dot in top-right corner
        BottomLeft,   ///< Dot in bottom-left corner
        TopLeft       ///< Dot in top-left corner
    };

    /**
     * @brief Constructor
     * @param window The widget whose icon will be flashed (must have setWindowIcon/windowIcon methods)
     * @param flashInterval Flash interval in milliseconds (default: 800ms)
     * @param dotSizeRatio Size of dot relative to icon size (default: 0.35, i.e., 35%)
     * @param dotColor Color of the recording indicator dot (default: red)
     * @param dotPosition Position of the dot on the icon (default: BottomRight)
     * @param parent Parent QObject
     */
    explicit IconFlasher(QWidget *window, int flashInterval = 800, 
                        double dotSizeRatio = 0.35, const QColor &dotColor = Qt::red,
                        DotPosition dotPosition = BottomRight, QObject *parent = nullptr);

    /**
     * @brief Start the flashing animation
     */
    void start();

    /**
     * @brief Stop the flashing animation and restore original icon
     */
    void stop();

    /**
     * @brief Check if flashing is currently active
     * @return true if flashing, false otherwise
     */
    bool isActive() const { return m_timer->isActive(); }

    /**
     * @brief Set the flash interval
     * @param interval Interval in milliseconds
     */
    void setFlashInterval(int interval);

    /**
     * @brief Get the current flash interval
     * @return Interval in milliseconds
     */
    int flashInterval() const { return m_timer->interval(); }

private slots:
    void toggleIcon();

private:
    void updateWindowIcon();
    QIcon createRecordingIcon(const QIcon &baseIcon);

    QWidget *m_window;
    QTimer *m_timer;
    QIcon m_originalIcon;
    QIcon m_recordingIcon;
    bool m_state;
    double m_dotSizeRatio;
    QColor m_dotColor;
    DotPosition m_dotPosition;
};

#endif // ICONFLASHER_H