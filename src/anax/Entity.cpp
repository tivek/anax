///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///

#include <anax/Entity.hpp>

#include <anax/World.hpp>

namespace anax
{
	Entity::Entity()
		: _world(nullptr)
	{
	}
	
	Entity::Entity(World& world, Entity::Id id)
		: _world(&world),
		  _id(id)
	{
	}
	
	World& Entity::getWorld() const
	{
		return *_world;
	}
	
	const Entity::Id& Entity::getId() const
	{
		return _id;
	}
	
	bool Entity::isValid() const
	{
		return getWorld().isValid(*this);
	}
	
	bool Entity::isActivated() const
	{
		return getWorld().isActivated(*this);
	}
	
	void Entity::activate()
	{
		getWorld().activateEntity(*this);
	}
	
	void Entity::deactivate()
	{
		getWorld().deactivateEntity(*this);
	}
	
	void Entity::kill()
	{
		getWorld().killEntity(*this);
	}
    
    /*
    void addComponent(BaseComponent* component)
    {
        addComponent(component, component->getTypeId());
    }
    */
	
	void Entity::removeAllComponents()
	{
		getWorld()._entityAttributes.componentStorage.removeAllComponents(*this);
	}
	
	ComponentArray Entity::getComponents() const
	{
		return getWorld()._entityAttributes.componentStorage.getComponents(*this);
	}
	
	ComponentTypeList Entity::getComponentTypeList() const
	{
		return getWorld()._entityAttributes.componentStorage.getComponentTypeList(*this);
	}
	
	bool Entity::operator==(const anax::Entity &entity) const
	{
		return _id == entity._id && entity._world == _world;
	}
	
	
	
	void Entity::addComponent(BaseComponent* component, detail::TypeId componentTypeId)
	{
		getWorld()._entityAttributes.componentStorage.addComponent(*this, component, componentTypeId);
	}
	
	void Entity::removeComponent(detail::TypeId componentTypeId)
	{
		getWorld()._entityAttributes.componentStorage.removeComponent(*this, componentTypeId);
	}
	
	BaseComponent& Entity::getComponent(detail::TypeId componentTypeId) const
	{
		return getWorld()._entityAttributes.componentStorage.getComponent(*this, componentTypeId);
	}
	
	bool Entity::hasComponent(detail::TypeId componentTypeId) const
	{
		return getWorld()._entityAttributes.componentStorage.hasComponent(*this, componentTypeId);
	}
}

