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

enum GameStatus { NOTINGAME, STARTINGGAME, SETUPGAME, INGAME };

class BattleFleetGUIApp : public AppNative {
public:
    
    void setup();
    void mouseDown( MouseEvent event );
    void update();
    void draw();
    
private:
    
    Game _game;
    
    int _inGameStatus;
    gl::Texture _backGround;
    
    gl::Texture _titleIcon;
    gl::Texture _startIcon;
    
    vector<gl::Fbo> _playerView;
    
    vector<gl::Texture> _playerBoard;
    vector<gl::Texture> _shipImages;
    vector<gl::Texture> _pinType;
    
};

// Does all initial setup for windows, pictures, textures, etc.
void BattleFleetGUIApp::setup() {
    
    setWindowSize(1600, 800);
    
    _playerView.push_back(gl::Fbo(1600, 800));
    _playerView.push_back(gl::Fbo(1600, 800));
    
    _inGameStatus = NOTINGAME;
      
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
            
        case NOTINGAME:{
            
            if ((event.getX() >= 600) && (event.getX() <= 1000) && (event.getY() >= 125) && (event.getY() <= 225)) {
                
                console() << "This is the title.\n";
                
            }
            
            else if ((event.getX() >= 675) && (event.getX() <= 925) && (event.getY() >= 300) && (event.getY() <= 400)) {
                
                _inGameStatus = STARTINGGAME;
                
                
            }
            
            else {
                
                console() << "out of bounds\n";
                
            }
            
            break;
            
        }
            

        case SETUPGAME: {

            // you can place ships or pins by changing the name and the index.
        
            if ((event.getX() >= 505) && (event.getX() <= 1165) && (event.getY() >= 105) && (event.getY() <= 765)) {
                
                console() << "player one set his ship up\n";
                gl::draw( _shipImages[0], Rectf(event.getX() - 25, event.getY() - 25, event.getX() + 25, event.getY() + 25));
                
                
            }
            
            
            
            
            
            
            
            

            break;

        }
            
            
            
    }
}

void BattleFleetGUIApp::update() {
    
    // Probably used to check when get is over/turn and/or other checkable functions.
    
}

void BattleFleetGUIApp::draw() {
    
    switch (_inGameStatus) {
        case NOTINGAME: {
            
            gl::draw( _backGround, getWindowBounds() );
            gl::draw( _titleIcon, Area( 600, 225, 1000, 125 ) );
            gl::draw( _startIcon, Area( 675, 300, 925, 400 ) );
            break;
            
        }
        case STARTINGGAME: {
            
            gl::clear();
            
            // x1, y1, x2, y2
            gl::draw( _backGround, Area( 400, 0, 1200, 800) );// Centered board
            
            
            // 660 by 660
            //
            // gl::drawSolidRect( Rectf( 505, 765, 1165, 105));
            
            
            
            
            //gl::setViewport( Area( 0, 800, 1600, 0));
            
            _inGameStatus = SETUPGAME;
            break;
            
        }
    
        case INGAME:{
            
            gl::clear();
            gl::draw( _playerView[PLAYERONE].getTexture() );
            
            break;
        }
        
        
            
    }
    
    
}

CINDER_APP_NATIVE( BattleFleetGUIApp, RendererGl )
