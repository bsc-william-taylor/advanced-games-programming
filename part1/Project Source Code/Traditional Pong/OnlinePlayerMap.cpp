
/**
*
* Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
*
* This software is provided 'as-is', without any
* express or implied warranty. In no event will
* the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute
* it freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgment
*    in the product documentation would be appreciated but
*    is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "Scenes.h"
#include "OnlinePlayerMap.h"

OnlinePlayerMap::OnlinePlayerMap(Bank * bank)
{
	this->bank = bank;
}

OnlinePlayerMap::~OnlinePlayerMap()
{
	SAFE_RELEASE(ball);
}

void OnlinePlayerMap::onRender(Renderer& renderer)
{
	renderer.renderTexture(&background);
	player1.render();
	player2.render();
	ball->render();

	hud.render(renderer);
}

void OnlinePlayerMap::giveDetails(std::string name, std::string client_name)
{
	player_name = std::string(name);
	
	if (player_name == "PLAYER1") {
		server.setImportPort(DEFAULT_PORT);
		server.setPacketSize(DEFAULT_SIZE);
	} else {
		client.setDestinationHostName(client_name);
		client.setExportPort(DEFAULT_PORT);
		client.setPacketSize(DEFAULT_SIZE);
		client.connect();
	}
}

void OnlinePlayerMap::onLoad(SceneManager& mgr, Renderer& renderer)
{
	background.create(&renderer, "data/map.png");
	background.setPosition(0, 0, 1920, 1080);
	hud.create(renderer);

	player1.load(PLAYER_ONE, renderer);
	player1.setBehaviour(new PlayerBehaviour(15, false));

	player2.load(PLAYER_TWO, renderer);
	player2.setBehaviour(new PlayerBehaviour(15, true));

	ball = new Ball(&renderer, bank);
	ball->setDirectionSpeed(90, 20, -20);
	ball->create(&mgr, &player1, &player2);

	click = bank->pop_item<Music>("mouse_click_music");
}

void OnlinePlayerMap::handleClientMessages(std::string network_message)
{
	int start = network_message.find("P2") + 3;
	int x, y;

	std::string player2 = network_message.substr(start);

	x = atoi(player2.substr(0, player2.find(":")).c_str());
	y = atoi(player2.substr(player2.find(":") + 1).c_str());

	this->player2.setPosition(x, y);
}

void OnlinePlayerMap::handleServerMessages(std::string network_message)
{
	if (network_message == "start")
	{
		ball->showBall();
	}
	else
	{
		int start = network_message.find("P1") + 3;
		int stop = network_message.find("|P2");
		int x, y, bx, by = 0.0;

		std::string player1 = network_message.substr(start, stop - start);

		x = atoi(player1.substr(0, player1.find(":")).c_str());
		y = atoi(player1.substr(player1.find(":") + 1).c_str());

		start = network_message.find("B:") + 2;
		stop = network_message.find("D:") - 1;

		std::string ball_str = network_message.substr(start, stop - start);

		bx = atoi(ball_str.substr(0, ball_str.find(":")).c_str());
		by = atoi(ball_str.substr(ball_str.find(":")+1).c_str());

		this->player1.setPosition(x, y);
		this->ball->setPosition(bx, by);
	}
}

void OnlinePlayerMap::onExit()
{
	if (player_name == "PLAYER1") {
		server.shutdown();
	} else {
		client.shutdown();
	}
}

void OnlinePlayerMap::onUpdate(SceneManager& scenes, Renderer&)
{
	player1.update();
	player2.update();
	ball->update();
	hud.update();

	if (player_name == "PLAYER1")
	{
		if (server.packetRecieved()) {
			handleClientMessages(server.getPacket().getData().data);

			BallBehaviour * behaviour = ball->getBehaviour();
			std::string serverMessage = "P1:";

			serverMessage += player1.getPositionAsString();
			serverMessage += "|";
			serverMessage += "P2:";
			serverMessage += player2.getPositionAsString();
			serverMessage += "|";

			serverMessage += (behaviour->getPositionAsString());
			server.sendString(serverMessage);
		}
	}
	else
	{
		if (client.packetRecieved()) {
			handleServerMessages(client.getPacket().getData().data);
			client.sendString("P2:" + player2.getPositionAsString());
		}
	}
}

void OnlinePlayerMap::onEnter()
{
	player1.clear();
	player2.clear();
	ball->hideBall();
	ball->reset();
	hud.enter();
}

void OnlinePlayerMap::onEvent(SceneManager& scenes, SDL_Event * e)
{
	if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)	{
		scenes.setScene(MENU);
	}

	if (player_name == "PLAYER1") {
		player1.event(*e);
		if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_SPACE) {
			server.sendString("start");
			ball->showBall();
		}
	} else {
		player2.event(*e);
	}
}
