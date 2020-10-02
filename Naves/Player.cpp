#include "Player.h"

Player::Player(float x, float y, Game* game) :Actor("res/jugador.png",x,y,35,35,game){
	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;
	aIdleRight = new Animation("res/jugador_idle_derecha.png", width, height,
		320, 40, 6, 8,true, game);
	aIdleLeft = new Animation("res/jugador_idle_izquierda.png", width, height,
		320, 40, 6, 8,true, game);
	aRunningRight = new Animation("res/jugador_corriendo_derecha.png", width, height,
		320, 40, 6, 8,true, game);
	aRunningLeft = new Animation("res/jugador_corriendo_izquierda.png", width, height,
		320, 40, 6, 8,true, game);
	aShootingRight = new Animation("res/jugador_disparando_derecha.png",
		width, height, 160, 40, 6, 4, false, game);
	aShootingLeft = new Animation("res/jugador_disparando_izquierda.png",
		width, height, 160, 40, 6, 4, false, game);

	animation = aIdleRight;

}
void Player::update() {
	if (invulnerableTime > 0) {
		invulnerableTime--;
	}

	bool endAnimation = animation->update();

	if (collisionDown == true) {
		onAir = false;
	}
	else {
		onAir = true;
	}

	// Acabo la animaci�n, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}

	// Establecer orientaci�n
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}

	// Selecci�n de animaci�n basada en estados
	if (state == game->stateShooting) {
		if (orientation == game->orientationRight) {
			animation = aShootingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aShootingLeft;
		}
	}
	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}
		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
	}


	if (shootTime > 0) {
		shootTime--;
	}
}

void Player::loseLife() {
	if (invulnerableTime <= 0) {
		if (lifes > 0) {
			lifes--;
			invulnerableTime = 100;
			// 100 actualizaciones 
		}
	}
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::jump() {
	if (!onAir) {
		vy = -16;
		onAir = true;
	}
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		state = game->stateShooting;
		shootTime = shootCadence;
		aShootingLeft->currentFrame = 0; //"Rebobinar" animaci�n
		aShootingRight->currentFrame = 0; //"Rebobinar" animaci�n
		Projectile* projectile = new Projectile(x, y, game);
		if (orientation == game->orientationLeft) {
			projectile->vx = projectile->vx * -1; // Invertir
		}
		return projectile;
	}
	else {
		return NULL;
	}
}


void Player::draw(float scrollX) {
	if (invulnerableTime == 0) {
		animation->draw(x - scrollX, y);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animation->draw(x - scrollX, y);
		}
	}

}


//nullptr