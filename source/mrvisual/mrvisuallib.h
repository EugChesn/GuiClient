#ifndef MRVISUALLIB_H
#define MRVISUALLIB_H

#include <QWidget>
#include "mrvisuallib_global.h"

class MRVisualPrivate;
class MRVISUALLIBSHARED_EXPORT MRVisualLib : public QWidget
{
    Q_OBJECT
public:
    MRVisualLib(QWidget *parent = nullptr);
    ~MRVisualLib();

    void rotate(float x, float y, float z);

private:
    MRVisualPrivate *mrVisualPrivate;
};

#endif // MRVISUALLIB_H
