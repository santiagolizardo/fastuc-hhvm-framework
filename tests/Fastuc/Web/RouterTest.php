<?hh // strict
namespace Fastuc\Web;

class WebRouterTest extends \PHPUnit_Framework_TestCase
{
	public function testGeneral()
	{
		$routes = new Vector<Route>;

		$router = new Router( $routes );
		$this->assertFalse( $router->exists( 'foo/bar' ) );
		$this->assertNull( $router->get( 'foo/bar' ) );
		$this->assertNull( $router->find( 'test.dev', '/foo/bar' ) );

		$routes = Vector<Route> {
			Route::build( 'user/view', 'foo/bar' )
				->withPath( 'foo/(?<lastname>.+)' )
				->withDomain( 'test.dev' )
		};
		$router = new Router( $routes );
		$this->assertTrue( $router->exists( 'foo/bar' ) );
		$this->assertNotNull( $router->get( 'foo/bar' ) );

		$route = $router->find( 'test.dev', 'foo/bar' );
		$this->assertNotNull( $route );
		$this->assertTrue( $route->getAttributes()->containsKey( 'lastname' ) );
		$this->assertEquals( 'bar', $route->getAttributes()['lastname'] );
		$this->assertEquals( 'user/view', $route->getController() );
	}
}

