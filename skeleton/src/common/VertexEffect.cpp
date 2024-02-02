#include "VertexEffect.h"
#include "utils/MathUtil.h"
#include "Skeleton.h"

using namespace skel;

JitterVertexEffect::JitterVertexEffect(float jitterX, float jitterY): _jitterX(jitterX), _jitterY(jitterY) {
}

void JitterVertexEffect::begin(Skeleton &skeleton) {
	SP_UNUSED(skeleton);
}

void JitterVertexEffect::transform(float &x, float &y, float &u, float &v, Color &light, Color &dark) {
	SP_UNUSED(u);
	SP_UNUSED(v);
	SP_UNUSED(light);
	SP_UNUSED(dark);
	float jitterX = _jitterX;
	float jitterY = _jitterY;
	x += MathUtil::randomTriangular(-jitterX, jitterX);
	y += MathUtil::randomTriangular(-jitterX, jitterY);
}

void JitterVertexEffect::end() {
}

void JitterVertexEffect::setJitterX(float jitterX) {
	_jitterX = jitterX;
}

float JitterVertexEffect::getJitterX() {
	return _jitterX;
}

void JitterVertexEffect::setJitterY(float jitterY) {
	_jitterY = jitterY;
}

float JitterVertexEffect::getJitterY() {
	return _jitterY;
}

SwirlVertexEffect::SwirlVertexEffect(float radius, Interpolation &interpolation):
	_centerX(0),
	_centerY(0),
	_radius(radius),
	_angle(0),
	_worldX(0),
	_worldY(0),
	_interpolation(interpolation) {
}

void SwirlVertexEffect::begin(Skeleton &skeleton) {
	_worldX = skeleton.getX() + _centerX;
	_worldY = skeleton.getY() + _centerY;
}

void SwirlVertexEffect::transform(float &positionX, float &positionY, float &u, float &v, Color &light, Color &dark) {
	SP_UNUSED(u);
	SP_UNUSED(v);
	SP_UNUSED(light);
	SP_UNUSED(dark);

	float x = positionX - _worldX;
	float y = positionY - _worldY;
	float dist = (float)MathUtil::sqrt(x * x + y * y);
	if (dist < _radius) {
		float theta = _interpolation.interpolate(0, _angle, (_radius - dist) / _radius);
		float cos = MathUtil::cos(theta), sin = MathUtil::sin(theta);
		positionX = cos * x - sin * y + _worldX;
		positionY = sin * x + cos * y + _worldY;
	}
}

void SwirlVertexEffect::end() {

}

void SwirlVertexEffect::setCenterX(float centerX) {
	_centerX = centerX;
}

float SwirlVertexEffect::getCenterX() {
	return _centerX;
}

void SwirlVertexEffect::setCenterY(float centerY) {
	_centerY = centerY;
}

float SwirlVertexEffect::getCenterY() {
	return _centerY;
}

void SwirlVertexEffect::setRadius(float radius) {
	_radius = radius;
}

float SwirlVertexEffect::getRadius() {
	return _radius;
}

void SwirlVertexEffect::setAngle(float angle) {
	_angle = angle * MathUtil::Deg_Rad;
}

float SwirlVertexEffect::getAngle() {
	return _angle;
}

void SwirlVertexEffect::setWorldX(float worldX) {
	_worldX = worldX;
}

float SwirlVertexEffect::getWorldX() {
	return _worldX;
}

void SwirlVertexEffect::setWorldY(float worldY) {
	_worldY = worldY;
}

float SwirlVertexEffect::getWorldY() {
	return _worldY;
}
