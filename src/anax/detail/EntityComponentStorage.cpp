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

#include <anax/detail/EntityComponentStorage.hpp>

#include <anax/detail/ContainerUtils.hpp>

namespace anax
{
	namespace detail
	{
		EntityComponentStorage::EntityComponentStorage(std::size_t entityAmount)
			: _componentEntries(entityAmount)
		{
		}
		
		void EntityComponentStorage::addComponent(Entity& entity, BaseComponent* component, TypeId componentTypeId)
		{
			assert(entity.isValid());
			
			auto index = entity.getId().index;
			auto& componentDataForEntity = _componentEntries[index];
			
			detail::EnsureCapacity(componentDataForEntity.components, componentTypeId);
			componentDataForEntity.components[componentTypeId].reset(component);
			
			detail::EnsureCapacity(componentDataForEntity.componentTypeList, componentTypeId);
			componentDataForEntity.componentTypeList[componentTypeId] = true;
		}
		
		void EntityComponentStorage::removeComponent(Entity& entity, TypeId componentTypeId)
		{
			assert(entity.isValid());
			
			auto index = entity.getId().index;
			auto& componentDataForEntity = _componentEntries[index];
			
			componentDataForEntity.components[componentTypeId].reset();
			componentDataForEntity.componentTypeList[componentTypeId] = false;
		}
		
		void EntityComponentStorage::removeAllComponents(Entity &entity)
		{
			auto index = entity.getId().index;
			auto& componentDataForEntity = _componentEntries[index];
			
			componentDataForEntity.components.clear();
			componentDataForEntity.componentTypeList.clear();
		}
		
		BaseComponent& EntityComponentStorage::getComponent(const Entity& entity, TypeId componentTypeId) const
		{
			assert(entity.isValid() && hasComponent(entity, componentTypeId) && "Entity is not valid or does not contain component");
			
			return *getComponentsImpl(entity)[componentTypeId];
		}
		
		ComponentTypeList EntityComponentStorage::getComponentTypeList(const Entity& entity) const
		{
			assert(entity.isValid());
			
			return _componentEntries[entity.getId().index].componentTypeList;
		}
		
		ComponentArray EntityComponentStorage::getComponents(const Entity& entity)  const
		{
			assert(entity.isValid());
			
			auto& componentsToConvert = getComponentsImpl(entity);
			
			std::vector<std::reference_wrapper<BaseComponent>> temp;
			temp.reserve(componentsToConvert.size());
			
			for(auto& i : componentsToConvert)
				temp.push_back(*i.get());
			
			return temp;
		}
		
		bool EntityComponentStorage::hasComponent(const Entity& entity, TypeId componentTypeId) const
		{
			assert(entity.isValid());

			auto& components = getComponentsImpl(entity);
			
			return components.size() > componentTypeId && components[componentTypeId] != nullptr;
		}
		
		void EntityComponentStorage::resize(std::size_t entityAmount)
		{
			_componentEntries.resize(entityAmount);
		}
		
        void EntityComponentStorage::clear()
        {
            _componentEntries.clear();
        }

		EntityComponentStorage::ImplComponentArray& EntityComponentStorage::getComponentsImpl(const Entity &e)
		{
			return _componentEntries[e.getId().index].components;
		}
		
		const EntityComponentStorage::ImplComponentArray& EntityComponentStorage::getComponentsImpl(const Entity &e) const
		{
			return _componentEntries[e.getId().index].components;
		}
	}
}
