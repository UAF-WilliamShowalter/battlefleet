#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Font.h"
#include "cinder/Text.h"

#include "BFBoard.h"
#include "BFShip.h"
#include "Game.h"
#include <vector>

using namespace ci;
using namespace ci::app;

using std::vector;

enum GameStatus { MENU, SETUPGAME, PLAYERSWITCHSETUP, INGAME, INGAMESWITCH, INGAMESHOWPIN, GAMEOVER };

const int X_OFFSET = 105;
const int Y_OFFSET = 105;
const int SCREEN_SIZE_X = 1600;
const int SCREEN_SIZE_Y = 800;
const int BOARD_SIZE = 660;
const int SQUARE_SIZE = BOARD_SIZE/BF_BOARD_SIZE;
const int BETWEEN_BOARDS = SCREEN_SIZE_X/2;
const int MAX_SHIPS = 17;

class BattleFleetGUIApp : public AppNative {
public:
    
    void setup();
    void mouseDown( MouseEvent event );
    void update();
    void draw();
    void drawPlayerPins(Player player);
	void drawPlayerShips(Player player);
	void drawBackground();

private:
	void drawTextureAtCoordinate(const vector<boardCoordinate> & coordinates, const gl::Texture & texture, unsigned int screenOffset) const;
	unsigned int calculateScreenOffset(Player player);
	bool clickInsideBoard(const MouseEvent & event);

private:
    
    Game _game;
    
    int _inGameStatus;
    gl::Texture _backGround;
    
    gl::Texture _titleIcon;
    gl::Texture _startIcon;
    gl::Texture _switchPlayerIcon;
    
    vector<gl::Texture> _playerBoard;
    vector<gl::Texture> _shipImages;
    vector<gl::Texture> _pinType;
    
};

// Does all initial setup for windows, pictures, textures, etc.
void BattleFleetGUIApp::setup() {
    
    setWindowSize(1600, 800);

    _inGameStatus = MENU;
      
    TextLayout title;
    title.setFont( Font("Arial", 36 ) );
    title.setColor( Color( 34, 45, 45 ) );
    title.addLine( " ---BattleFleet--- " );
    _titleIcon = gl::Texture( title.render( true, false ) );
    
    TextLayout start;
    start.setFont( Font("Arial", 25 ) );
    start.setColor(Color( 1, 1, .1f ));
    start.addLine( " -New Game- ");
    _startIcon = gl::Texture( start.render( true, false ) );
    
    TextLayout switchPlayer;
    switchPlayer.setFont( Font("Arial", 25 ) );
    switchPlayer.setColor(Color( 1, 1, .1f ));
    switchPlayer.addLine( " Hand computer to the other player ");
    switchPlayer.addCenteredLine( " Click to continue ");
    _switchPlayerIcon = gl::Texture( switchPlayer.render( true, false ) );
    
    _backGround = gl::Texture( loadImage( loadResource( "BattleFleetBoard.jpg" ) ) );
    
    _shipImages.push_back(gl::Texture( loadImage( loadResource( "PatrolBoat.png" ) ) ) );
    _shipImages.push_back(gl::Texture( loadImage( loadResource( "Submarine.png" ) ) ) );
    _shipImages.push_back(gl::Texture( loadImage( loadResource( "Cruiser.png" ) ) ) );
    _shipImages.push_back(gl::Texture( loadImage( loadResource( "BattleShip.png" ) ) ) );
    _shipImages.push_back(gl::Texture( loadImage( loadResource( "AircraftCarrier.png" ) ) ) );

    _pinType.push_back(gl::Texture( loadImage( loadResource( "WhitePin.png" ) ) ) );
    _pinType.push_back(gl::Texture( loadImage( loadResource( "RedPin.png" ) ) ) );
    
}

void BattleFleetGUIApp::mouseDown( MouseEvent event ) {
    /* The loop is as follows
     mouse events (mouseDown) ---> update() -----> draw
     if you need anything text me or check the cinder library documentation
     */
    
    switch (_inGameStatus){
            
        case MENU:{
            
            if ((event.getX() >= 675) && (event.getX() <= 925) && (event.getY() >= 300) && (event.getY() <= 400)) {
                
                _inGameStatus = SETUPGAME;
                
                
            }
            
            break;
            
        }
            

        case SETUPGAME: {

            if (clickInsideBoard(event)) {

				unsigned int x_coord = (event.getX()-X_OFFSET)/SQUARE_SIZE;
				unsigned int y_coord = (event.getY()-Y_OFFSET)/SQUARE_SIZE;

				_game.placePlayerShips(_game.getActivePlayer(), x_coord, y_coord, 1, NORTH);

				if (!(_game.getPlayerShips(_game.getActivePlayer()).size() < MAX_SHIPS))
				{
					if (_game.getActivePlayer() == PLAYERONE)
					{
						_game.switchPlayer();
                        _inGameStatus = PLAYERSWITCHSETUP;
					}
					else
					{
						_game.switchPlayer();
						_inGameStatus = INGAMESWITCH;
					}
				}
            }

            break;

        }
            
        case PLAYERSWITCHSETUP: {
            
            _inGameStatus = SETUPGAME;
            
            break;
            
        }
            
        case INGAMESWITCH: {
            
            _inGameStatus = INGAME;
            
            break;
        }
            
        case INGAME: {
            
            if (clickInsideBoard(event)) {
                
                unsigned int x_coord = (event.getX()-X_OFFSET)/SQUARE_SIZE;
                unsigned int y_coord = (event.getY()-Y_OFFSET)/SQUARE_SIZE;
                
                if (_game.attackOpponent(_game.getActivePlayer(), x_coord, y_coord))
                    _inGameStatus = INGAMESHOWPIN;
                
            }
            
            break;
        }
            
        case INGAMESHOWPIN: {
            
            _game.switchPlayer();
            _inGameStatus = INGAMESWITCH;
            
            if (_game.hasEnded()){
                
                _inGameStatus = GAMEOVER;
                
            }
            
            break;
        }
            
    }
}

void BattleFleetGUIApp::update() {
}

void BattleFleetGUIApp::draw() {
    
    switch (_inGameStatus) {
        case MENU: {
            
            gl::draw( _backGround, getWindowBounds() );
            gl::draw( _titleIcon, Area( 600, 225, 1000, 125 ) );
            gl::draw( _startIcon, Area( 675, 300, 925, 400 ) );
            break;
            
        }
            
        case SETUPGAME: {
            
            gl::clear();
            drawBackground();
            drawPlayerShips(_game.getActivePlayer());
            
            break;
            
        }
    
        case PLAYERSWITCHSETUP: {
            
            gl::clear();
            gl::draw( _switchPlayerIcon, Area( 400, 200, 1200, 600 ));
            
            break;
            
        }
        
        case INGAMESWITCH: {
            
            gl::clear();
            gl::draw( _switchPlayerIcon, Area( 400, 200, 1200, 600 ));
            
            break;
        }
            
        case INGAME: {
            
            gl::clear();
            drawBackground();
            drawPlayerShips(_game.getActivePlayer());
            drawPlayerPins(_game.getActivePlayer());
            drawPlayerPins(_game.getInactivePlayer());
            
            break;
        }
            
        case INGAMESHOWPIN: {
            
            gl::clear();
            drawBackground();
            drawPlayerShips(_game.getActivePlayer());
            drawPlayerPins(_game.getActivePlayer());
            drawPlayerPins(_game.getInactivePlayer());
            
            break;
        }
            
        case GAMEOVER: {
            
            gl::clear();
            drawBackground();
            
            drawPlayerShips(PLAYERONE);
            drawPlayerShips(PLAYERTWO);
            
            drawPlayerPins(PLAYERONE);
            drawPlayerPins(PLAYERTWO);
            
            
            break;
        }
            
    }
}

void BattleFleetGUIApp::drawPlayerShips(Player player)
{

	unsigned int screenOffset = calculateScreenOffset(player);

	vector<boardCoordinate> coordinates;
	for (auto ship : _game.getPlayerShips(player))
	{
		coordinates.push_back(ship.getPosition());
	}

	drawTextureAtCoordinate(coordinates, _shipImages[0], screenOffset);
}

void BattleFleetGUIApp::drawBackground()
{
	gl::draw( _backGround, Area( 0, 0, BETWEEN_BOARDS, SCREEN_SIZE_Y) );			// Left board
	gl::draw( _backGround, Area( BETWEEN_BOARDS, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y) );// Right board
}

void BattleFleetGUIApp::drawPlayerPins(Player player) {
    
	unsigned int screenOffset = calculateScreenOffset(player);

	drawTextureAtCoordinate(_game.getPlayerMissPins(player),_pinType[0], screenOffset);

	drawTextureAtCoordinate(_game.getPlayerHitPins(player),_pinType[1], screenOffset);
    
}

void BattleFleetGUIApp::drawTextureAtCoordinate(const vector<boardCoordinate> & coordinates, const gl::Texture & texture, unsigned int screenOffset) const
{
	for (auto coordinate : coordinates )
	{

		gl::draw( texture, Rectf(coordinate.first*SQUARE_SIZE+X_OFFSET + screenOffset,
									 coordinate.second*SQUARE_SIZE+Y_OFFSET,
									 (coordinate.first+1)*SQUARE_SIZE+X_OFFSET-5 + screenOffset,
									 (coordinate.second+1)*SQUARE_SIZE+Y_OFFSET-5));

	}
}

unsigned int BattleFleetGUIApp::calculateScreenOffset(Player player){
	unsigned int screenOffset = 0;

	if (player == _game.getActivePlayer()){

		screenOffset = BETWEEN_BOARDS;

	}

	if (_game.hasEnded()){

		if (player == PLAYERONE)
			screenOffset = 0;
		else
			screenOffset = BETWEEN_BOARDS;

	}

	return screenOffset;
}

bool BattleFleetGUIApp::clickInsideBoard(const MouseEvent & event){
	return ((event.getX() >= X_OFFSET) && (event.getX() <= X_OFFSET+BOARD_SIZE) &&
			(event.getY() >= Y_OFFSET) && (event.getY() <= Y_OFFSET+BOARD_SIZE));
}

CINDER_APP_NATIVE( BattleFleetGUIApp, RendererGl )
