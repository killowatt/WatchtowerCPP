#pragma once

namespace Watchtower
{
	class Entity
	{
	public:
		bool Active;
		bool Visible;

		virtual bool Update() { return false; }
		virtual void Render() { }

		Entity() : Active(false), Visible(false) { }
	};
}