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

#include "lest.hpp"

#include <anax/Entity.hpp>
#include <anax/World.hpp>

#include "Components.hpp"

const lest::test specification[] =
{
	"Invalid entity handles (killing entities)", []
	{
		anax::World world;
		
		auto e1 = world.createEntity(); // create an entity
		e1.kill(); // kill it
		
		EXPECT(e1.isValid());
	},
	
	"Duplicate invalid (killed) entity handles", []
	{
		anax::World world;

		auto e1 = world.createEntity(); // create an entity
		e1.kill(); // kill it
		
		// refresh the world (so that the ID will be invalid)
		world.refresh();
		
		// create another handle,
		// that is the same as the previous
		anax::Entity e2 = e1;
		
		EXPECT(!e2.isValid()); // should be invalid
	},
	
	"Activating and deactivating entities", []
	{
		anax::World world;
		
		auto e1 = world.createEntity();
		e1.activate();
		
		EXPECT(!e1.isActivated()); // should not be activated
		
		world.refresh();
		
		EXPECT(e1.isActivated()); // should be activated
		
		e1.deactivate();
		
		EXPECT(e1.isActivated()); // should be still activated

		world.refresh();
		
		EXPECT(!e1.isActivated()); // should not be activated
	},
	
	"Adding components", []
	{
		anax::World world;
		
		auto e = world.createEntity();
		e.addComponent<PositionComponent>();
		
		EXPECT(e.hasComponent<PositionComponent>());
	},
	
	"Removing components", []
	{
		anax::World world;
		
		auto e = world.createEntity();
		e.addComponent<PositionComponent>();
		e.removeComponent<PositionComponent>();
		
		EXPECT(!e.hasComponent<PositionComponent>());
	},
	
	"Removing all components", []
	{
		anax::World world;
		
		auto e = world.createEntity();
		e.addComponent<PositionComponent>();
		e.addComponent<VelocityComponent>();
		
		e.removeAllComponents();
		
		EXPECT(!e.hasComponent<PositionComponent>() && !e.hasComponent<VelocityComponent>());
	}
};

int main()
{
	return lest::run(specification);
}