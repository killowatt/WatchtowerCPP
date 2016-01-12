#pragma once

namespace Watchtower
{
	class Entity
	{
	public:
		bool Active;
		bool Visible;
		bool Finished;

		virtual void Update() { }
		virtual void Render() { }

		Entity() { }
	};
}