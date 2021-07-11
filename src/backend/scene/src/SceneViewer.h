#pragma once
#include <QtQuick/QQuickFramebufferObject>
#include <QTimer>


class SceneRenderer;
class SceneViewer : public QQuickFramebufferObject
{
    Q_OBJECT
	Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
	Q_PROPERTY(QUrl assets READ assets WRITE setAssets)
	Q_PROPERTY(int curFps READ curFps)
	Q_PROPERTY(int fps READ fps WRITE setFps NOTIFY fpsChanged)
	Q_PROPERTY(int fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)

    friend class SceneRenderer;
public:
	enum FillMode {
		STRETCH,
		ASPECTFIT,	
		ASPECTCROP
	};
    Q_ENUM(FillMode)

public:
    SceneViewer(QQuickItem * parent = 0);
    virtual ~SceneViewer();
    virtual Renderer *createRenderer() const;

	QUrl source() const;
	QUrl assets() const;
	int curFps() const;
	int fps() const;
	int fillMode() const;

	void setSource(const QUrl& source);
	void setAssets(const QUrl& assets);
	void setFps(int);
	void setFillMode(int);

	Q_INVOKABLE void setAcceptMouse(bool);
	Q_INVOKABLE void setAcceptHover(bool);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void hoverMoveEvent(QHoverEvent *event);

public slots:
	void play();
	void pause();

signals:
	void onUpdate();
	void sourceChanged();
	void fpsChanged();
	void fillModeChanged();

private:
	QUrl m_source;
	QUrl m_assets;
    QTimer m_updateTimer;
	QPointF m_mousePos;
	bool m_paused;
	int m_fps;
	int m_curFps;
	int m_fillMode;
	void* m_wgl;
};
