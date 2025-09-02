mat3 angle2_to_vector3_matrix(vec2 angle) {
    float pitch = angle.x;
    float yaw = angle.y;
    
    float cos_pitch = cos(pitch);
    float sin_pitch = sin(pitch);
    float cos_yaw = cos(yaw);
    float sin_yaw = sin(yaw);
    
    return mat3(
        cos_yaw, 0.0, -sin_yaw,
        sin_yaw * sin_pitch, cos_pitch, cos_yaw * sin_pitch,
        sin_yaw * cos_pitch, -sin_pitch, cos_yaw * cos_pitch
    );
}
