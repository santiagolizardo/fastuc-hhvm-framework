<?hh // strict
namespace Fastuc\Web;

class WebRouterTest extends \PHPUnit_Framework_TestCase
{
	public function testGeneral()
	{
		$routes = array();

		$router = new Router( $routes );
		$this->assertFalse( $router->exists( 'foo/bar' ) );
		$this->assertNull( $router->get( 'foo/bar' ) );
		$this->assertNull( $router->find( 'test.dev', '/foo/bar' ) );

		$routes = array(
			'foo/bar' => array(
				'domain' => 'test.dev',
				'pattern' => 'foo/(?<lastname>.+)',
				'controller' => 'user/view',
			),
		);
		$router = new Router( $routes );
		$this->assertTrue( $router->exists( 'foo/bar' ) );
		$this->assertNotNull( $router->get( 'foo/bar' ) );

		$route = $router->find( 'test.dev', 'foo/bar' );
		$this->assertNotNull( $route );
		$this->assertArrayHasKey( 'lastname', $route['attributes'] );
		$this->assertEquals( 'bar', $route['attributes']['lastname'] );
		$this->assertEquals( 'user/view', $route['controller'] );
	}
}

