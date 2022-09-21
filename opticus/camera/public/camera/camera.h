#pragma once

#include <glm/glm.hpp>

using vec2 = glm::highp_vec2;
using vec3 = glm::highp_vec3;
using vec4 = glm::highp_vec4;
using mat4 = glm::highp_mat4;
using quat = glm::highp_quat;

class Camera {
public:
    Camera();
    ~Camera();

    void        set_viewport(const Recti& viewport);
    void        set_fov_y(const float fovy);
    void        SetViewPlanes(const float nearZ, const float farZ);
    void        set_position(const vec3& pos);

    void        look_at(const vec3& pos, const vec3& target);
    void        move(const float side, const float direction);
    void        rotate(const float angleX, const float angleY);

    float       get_near_plane() const;
    float       get_far_plane() const;
    float       get_fov_y() const;

    const mat4& get_projection() const;
    const mat4& get_transform() const;

    const vec3& get_position() const;
    const vec3& get_direction() const;
    const vec3  get_up() const;
    const vec3  get_slide() const;

private:
    void        make_projection();
    void        make_transform();

private:
    Recti   m_viewport;
    float   m_fov_y;
    float   m_near_z;
    float   m_far_z;
    vec3    m_position;
    vec3    m_direction;
    quat    m_rotation;
    mat4    m_projection;
    mat4    m_transform;
};