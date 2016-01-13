#include "Player.h"
using namespace Watchtower;

bool Player::Update()
{
	return false;
}
void Player::Render() { }

Player::Player()
{
	Active = true;
	Visible = true;
}