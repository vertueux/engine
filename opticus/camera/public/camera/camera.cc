#include "camera/camera.h"

static const vec3 s_camera_up(0.0f, 1.0f, 0.0f);

quat q_angle_axis(const float angleRad, const vec3& axis) { return glm::angleAxis(angleRad, axis); }
vec3 q_rotate(const quat& q, const vec3& v) { return glm::rotate(q, v); }
vec3 cross(const vec3& a, const vec3& b) { return glm::cross(a, b); }
quat normalize(const quat& q) { return glm::normalize(q); }
vec3 normalize(const vec3& v) { return glm::normalize(v); }
constexpr auto mat_projection = glm::perspectiveRH_ZO<float>;

constexpr auto mat_look_at = glm::lookAtRH<float, glm::highp>;

Camera::Camera()
    : m_fov_y(65.0f)
    , m_near_z(1.0f)
    , m_far_z(1000.0f)
    , m_position(0.0f, 0.0f, 0.0f)
    , m_direction(0.0f, 0.0f, 1.0f)
{
}

Camera::~Camera() {
}

void Camera::set_viewport(const Recti& viewport) {
    m_viewport = viewport;
    this->make_projection();
}

void Camera::set_fov_y(const float fovy) {
    m_fov_y = fovy;
    this->make_projection();
}

void Camera::set_view_planes(const float nearZ, const float farZ) {
    m_near_z = nearZ;
    m_far_z = farZ;
    this->make_projection();
}

void Camera::set_position(const vec3& pos) {
    m_position = pos;
    this->make_transform();
}

void Camera::look_at(const vec3& pos, const vec3& target) {
    m_position = pos;
    m_direction = normalize(target - pos);

    this->make_transform();
}

void Camera::move(const float side, const float direction) {
    vec3 camera_side = normalize(cross(m_direction, s_camera_up));

    m_position += camera_side * side;
    m_position += m_direction * direction;

    this->make_transform();
}

void Camera::rotate(const float angleX, const float angleY) {
    vec3 side = cross(m_direction, s_camera_up);
    quat pitch_q = q_angle_axis(Deg2Rad(angleY), side);
    quat heading_q = q_angle_axis(Deg2Rad(angleX), s_camera_up);
    //add the two quaternions
    quat temp = normalize(pitch_q * heading_q);
    // finally rotate our direction
    m_direction = normalize(q_rotate(temp, m_direction));

    this->make_transform();
}

float Camera::get_near_plane() const {
    return m_near_z;
}

float Camera::get_far_plane() const {
    return m_far_z;
}

float Camera::get_fov_y() const {
    return m_fov_y;
}

const mat4& Camera::get_projection() const {
    return m_projection;
}

const mat4& Camera::get_transform() const {
    return m_transform;
}

const vec3& Camera::get_position() const {
    return m_position;
}

const vec3& Camera::get_direction() const {
    return m_direction;
}

const vec3 Camera::get_up() const {
    return vec3(m_transform[0][1], m_transform[1][1], m_transform[2][1]);
}

const vec3 Camera::get_slide() const {
    return vec3(m_transform[0][0], m_transform[1][0], m_transform[2][0]);
}

void Camera::make_projection() {
    const float aspect = static_cast<float>(m_viewport.right - m_viewport.left) / static_cast<float>(m_viewport.bottom - m_viewport.top);
    m_projection = mat_projection(Deg2Rad(m_fov_y), aspect, m_near_z, m_far_z);
}

void Camera::make_transform() {
    m_transform = mat_look_at(m_position, m_position + m_direction, s_camera_up);
}