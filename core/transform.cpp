#include "transform.h"

Transform::Transform(const Matrix4x4 &mat)
    :m_(mat),
    m_inv_(mat.inverse())
{
}

