#include <my_rviz.h>

#include <QSlider>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>



#include <QtQml/QQmlContext>
#include <QColor>


// BEGIN_TUTORIAL
// Constructor for MyViz.  This does most of the work of the class.
MyViz::MyViz( QWindow* parent )
  : QQuickView( parent )
  , manager_(nullptr)
  , grid_(nullptr)
  , render_window_()
  , render_panel_(nullptr)
  , cell_size_percent_(0)
  , thickness_percent_(0)

{
    connect(this, &MyViz::beforeRendering, this, &MyViz::initializeOgre, Qt::DirectConnection);
    connect(this, &MyViz::ogreInitialized, this, &MyViz::addContent);
//  render_panel_ = new rviz::RenderPanel();

//  manager_ = new rviz::VisualizationManager( render_panel_ );
//  render_panel_->initialize( manager_->getSceneManager(), manager_ );
//  manager_->initialize();
//  manager_->startUpdate();

//  // Create a Grid display.
//  grid_ = manager_->createDisplay( "rviz/Grid", "adjustable grid", true );
//  ROS_ASSERT( grid_ != NULL );

//  // Configure the GridDisplay the way we like it.
//  grid_->subProp( "Line Style" )->setValue( "Billboards" );
//  grid_->subProp( "Color" )->setValue( Qt::yellow );

//  // Initialize the slider values.
//  thickness_slider->setValue( 25 );
//  cell_size_slider->setValue( 10 );
}


void MyViz::initializeOgre()
{
    // we only want to initialize once
    disconnect(this, &MyViz::beforeRendering, this, &MyViz::initializeOgre);
    render_panel_ = new rviz::RenderPanel(render_window_);
    render_panel_->initialize()
    manager_ = new rviz::VisualizationManager(render_panel_);
    manager_->initialize();
    manager_->startUpdate();


    emit(ogreInitialized());
}


void MyViz::addContent()
{
    // Create a Grid display.
    grid_ = manager_->createDisplay( "rviz/Grid", "adjustable grid", true );
    ROS_ASSERT( grid_ != NULL );

    // Configure the GridDisplay the way we like it.
    grid_->subProp( "Line Style" )->setValue( "Billboards" );
    grid_->subProp( "Color" )->setValue( QColor("Yellow") );

    // expose objects as QML globals
    rootContext()->setContextProperty("Window", this);
    rootContext()->setContextProperty("grid_", grid_);

    // load the QML scene
    setResizeMode(QQuickView::SizeRootObjectToView);
    setSource(QUrl("qrc:/qml/Page2Form.qml"));
}



// Destructor.
MyViz::~MyViz()
{
  delete manager_;
}

// This function is a Qt slot connected to a QSlider's valueChanged()
// signal.  It sets the line thickness of the grid by changing the
// grid's "Line Width" property.
void MyViz::setThickness( int thickness_percent )
{
  if( grid_ != NULL )
  {
    grid_->subProp( "Line Style" )->subProp( "Line Width" )->setValue( thickness_percent / 100.0f );
  }
}

// This function is a Qt slot connected to a QSlider's valueChanged()
// signal.  It sets the cell size of the grid by changing the grid's
// "Cell Size" Property.
void MyViz::setCellSize( int cell_size_percent )
{
  if( grid_ != NULL )
  {
    grid_->subProp( "Cell Size" )->setValue( cell_size_percent / 10.0f );
  }
}
