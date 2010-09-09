#ifndef PLLAYOUT_H
#define PLLAYOUT_H

#include <QLayout>
#include <QResizeEvent>




class PLLayout : public QLayout
{
    Q_OBJECT

public:
    PLLayout();
    ~PLLayout();
    //the main API methods
    int setLLayout(QLayout *clientlayout);
    int setPLayout(QLayout *clientlayout);
    void activatePLayout();
    void activateLLayout();
    //re-implementation of QLayout Methods, as needed
    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    void setGeometry(const QRect &rect);
    bool hasHeightForWidth() const;
    int heightForWidth( int ) const;
    QLayoutItem * itemAt(int index ) const;
    QLayoutItem * takeAt ( int index );
    int count() const;

    //a convenience method for the parent widgets event handler
    void resizeEvent(QResizeEvent* event);

protected:
    //these two may be promoted to public, when extending to more generic use cases
    void activateLayout(int idx);
    int newLayout(QLayout *clientlayout);

private:

    QList<QLayout*> m_layoutList;
    int m_numOfClients;
    int m_currentLayoutIdx;

    int m_portraitLayoutIdx;
    int m_landscapeLayoutIdx;
    int getLayoutIdx()const ;

    bool m_hasPLayout;
    bool m_hasLLayout;
    bool m_isPLayout;
    bool m_isLLayout;

    void redrawParent();
};

#endif // PLLAYOUT_H
