#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Font.h"
#include "cinder/Text.h"
#include "cinder/gl/Fbo.h" // Frame Buffer Objects

#include "BFBoard.h"
#include "BFShip.h"
#include "Game.h"
#include <vector>

using namespace ci;
using namespace ci::app;

using std::vector;

enum GameStatus { MENU, SETUPGAME, PLAYERSWITCHSETUP, INGAME, INGAMESWITCH };

const int X_OFFSET = 105;
const int Y_OFFSET = 105;
const int BOARD_SIZE = 660;
const int SQUARE_SIZE = BOARD_SIZE/BF_BOARD_SIZE;
const int BETWEEN_BOARDS = 800;

class BattleFleetGUIApp : public AppNative {
public:
    
    void setup();
    void mouseDown( MouseEvent event );
    void update();
    void draw();
	void drawActivePlayerShips();
	void drawBackground();
    
private:
    
    Game _game;
    
    int _inGameStatus;
    gl::Texture _backGround;
    
    gl::Texture _titleIcon;
    gl::Texture _startIcon;
    gl::Texture _switchPlayerIcon;
    
    vector<gl::Fbo> _playerView;
    
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
            
            if ((event.getX() >= 600) && (event.getX() <= 1000) && (event.getY() >= 125) && (event.getY() <= 225)) {
                
                console() << "This is the title.\n";
                
            }
            
            else if ((event.getX() >= 675) && (event.getX() <= 925) && (event.getY() >= 300) && (event.getY() <= 400)) {
                
                _inGameStatus = SETUPGAME;
                
                
            }
            
            else {
                
                console() << "out of bounds\n";
                
            }
            
            break;
            
        }
            

        case SETUPGAME: {

            if ((event.getX() >= X_OFFSET) && (event.getX() <= X_OFFSET+BOARD_SIZE) &&
				(event.getY() >= Y_OFFSET) && (event.getY() <= Y_OFFSET+BOARD_SIZE)) {

				unsigned int x_coord = (event.getX()-X_OFFSET)/SQUARE_SIZE;
				unsigned int y_coord = (event.getY()-Y_OFFSET)/SQUARE_SIZE;

				_game.placePlayerShips(_game.playerTurn(), x_coord, y_coord, 1, NORTH);

                console() << "player one set his ship up\n";
                console() << event.getPos();

				if (!(_game.getPlayerShips(_game.playerTurn()).size()<5))
				{
					if (_game.playerTurn() == PLAYERONE)
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
            
            
            
    }
}

void BattleFleetGUIApp::update() {
    
    // Probably used to check when get is over/turn and/or other checkable functions.
    
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
            drawActivePlayerShips();
            
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
            
    }
    
    
}

void BattleFleetGUIApp::drawActivePlayerShips()
{
	for (auto ship : _game.getPlayerShips(_game.playerTurn()))
	{
		boardCoordinate shipCoords = ship.getPosition();
		gl::draw( _shipImages[0], Rectf(shipCoords.first*SQUARE_SIZE+X_OFFSET+BETWEEN_BOARDS,
										shipCoords.second*SQUARE_SIZE+Y_OFFSET,
										(shipCoords.first+1)*SQUARE_SIZE+X_OFFSET-5+BETWEEN_BOARDS,
										(shipCoords.second+1)*SQUARE_SIZE+Y_OFFSET-5));

	}
}

void BattleFleetGUIApp::drawBackground()
{
	gl::draw( _backGround, Area( 0, 0, 800, 800) );// Player 1 board
	gl::draw( _backGround, Area( 800, 0, 1600, 800) );// Player 2 board
}

CINDER_APP_NATIVE( BattleFleetGUIApp, RendererGl )
