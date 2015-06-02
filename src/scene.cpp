#include "scene.hpp"
#include <iostream>

SceneNode::SceneNode(const std::string& name)
  : m_name(name)
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::rotate(char axis, double angle)
{
  std::cerr << "Stub: Rotate " << m_name << " around " << axis << " by " << angle << std::endl;
  // Fill me in

    Matrix4x4 r;

    angle = angle * M_PI/ 180.0;

    double c = cos(angle);
    double s = sin(angle);

    Vector4D r1,r2,r3,r4;

    if (axis == 'x') {
	r1 = Vector4D(1, 0, 0, 0);
	r2 = Vector4D(0, c, -s, 0);
	r3 = Vector4D(0, s, c, 0);
	r4 = Vector4D(0, 0, 0, 1);
    } else if (axis == 'y') {
	r1 = Vector4D(c, 0, s, 0);
	r2 = Vector4D(0, 1, 0, 0);
	r3 = Vector4D(-s, 0, c, 0);
	r4 = Vector4D(0, 0, 0, 1);
    } else if (axis == 'z') { 
	r1 = Vector4D(c, -s, 0, 0);
	r2 = Vector4D(s, c, 0, 0);
	r3 = Vector4D(0, 0, 1, 0);
	r4 = Vector4D(0, 0, 0, 1);
    }

    r = Matrix4x4(r1, r2, r3, r4);

    m_trans = m_trans * r;
    m_invtrans = m_trans.invert();


}

void SceneNode::scale(const Vector3D& amount)
{
  std::cerr << "Stub: Scale " << m_name << " by " << amount << std::endl;
  // Fill me in

  Matrix4x4 s;

  double x = amount[0];
  double y = amount[1];
  double z = amount[2];

  Vector4D r1(x, 0, 0, 0);
  Vector4D r2(0, y, 0, 0);
  Vector4D r3(0, 0, z, 0);
  Vector4D r4(0, 0, 0, 1);

  s = Matrix4x4(r1, r2, r3, r4);

  m_trans = m_trans * s;
  m_invtrans = m_trans.invert();


}

void SceneNode::translate(const Vector3D& amount)
{
  std::cerr << "Stub: Translate " << m_name << " by " << amount << std::endl;
  // Fill me in

  Matrix4x4 t;

  double x = amount[0];
  double y = amount[1];
  double z = amount[2];

  Vector4D r1(1, 0, 0, x);
  Vector4D r2(0, 1, 0, y);
  Vector4D r3(0, 0, 1, z);
  Vector4D r4(0, 0, 0, 1);

  t = Matrix4x4(r1, r2, r3, r4);

  m_trans = m_trans * t;
  m_invtrans = m_trans.invert();
}

bool SceneNode::is_joint() const
{
  return false;
}

SceneNode *SceneNode::find(std::string name) {
  if (m_name == name) {
    return this;
  }
  for (ChildList::const_iterator it = m_children.begin(), end = m_children.end(); it != end; ++it) {
    SceneNode *node = (*it)->find(name);
    if (node) {
      return node;
    }
  }
  return NULL;
}

IntSection SceneNode::intsect(Ray ray) {

    IntSection i;

    ray.p = m_invtrans * ray.p;
    ray.dir = m_invtrans * ray.dir;

    //ray.dir.normalize();

    for (SceneNode::ChildList::const_iterator it = m_children.begin(), end = m_children.end(); it != end; it++) {

	SceneNode *node = *it;

	IntSection j = node->intsect(ray);

	if ( j.ishit ) {
	    if ( !i.ishit || j.t < i.t ) {
		i = j;
	    } 
	}

    }

    if ( i.ishit ) {
	i.p = m_trans * i.p;
	i.n = m_invtrans.transpose() * i.n;

	i.n.normalize();
    }

    return i;

}

JointNode::JointNode(const std::string& name)
  : SceneNode(name)
{
}

JointNode::~JointNode()
{
}

bool JointNode::is_joint() const
{
  return true;
}

void JointNode::set_joint_x(double min, double init, double max)
{
  m_joint_x.min = min;
  m_joint_x.init = init;
  m_joint_x.max = max;
}

void JointNode::set_joint_y(double min, double init, double max)
{
  m_joint_y.min = min;
  m_joint_y.init = init;
  m_joint_y.max = max;
}

GeometryNode::GeometryNode(const std::string& name, Primitive* primitive)
  : SceneNode(name),
    m_primitive(primitive)
{
}

GeometryNode::~GeometryNode()
{
}

IntSection GeometryNode::intsect(Ray ray) {

    IntSection i;

    ray.p = m_invtrans * ray.p;
    ray.dir = m_invtrans * ray.dir;

    //ray.dir.normalize();

    i = m_primitive->intsect(ray);
    if (i.ishit) {
	i.m = m_material;
    }

    for (SceneNode::ChildList::const_iterator it = m_children.begin(), end = m_children.end(); it != end; it++) {

	SceneNode *node = *it;

	IntSection j = node->intsect(ray);

	if ( j.ishit ) {
	    if ( !i.ishit || j.t < i.t ) {
		i = j;
	    } 
	}

    }

    if ( i.ishit ) {
	i.p = m_trans * i.p;
	i.n = m_invtrans.transpose() * i.n;

	i.n.normalize();
    }

    return i;

}
 
