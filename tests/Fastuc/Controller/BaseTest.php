<?hh // strict
namespace Fastuc\Controller;

class BaseTest extends \PHPUnit_Framework_TestCase
{
	public function setUp()
	{
		$_SERVER['REQUEST_URI'] = '/foo/bar';
		$_SERVER['SERVER_PROTOCOL'] = 'HTTP';
	}

	public function tearDown()
	{
		unset( $_SERVER['REQUEST_URI'] );
		unset( $_SERVER['SERVER_PROTOCOL'] );
	}

	public function testAttributes()
	{
		$controller = new Base;
		$this->assertEmpty( $controller->getAttributes() );

		$this->assertFalse( $controller->issetAttribute( 'name' ) );
		$this->assertNull( $controller->getAttribute( 'name' ) );

		$controller->setAttribute( 'name', 'Test Foobar' );
		$this->assertTrue( $controller->issetAttribute( 'name' ) );
		$this->assertEquals( 'Test Foobar', $controller->getAttribute( 'name' ) );
	}

	public function testHttpMethodNotAllowed()
	{
		$response = $this->getMock( '\Fastuc\Http\Response', array( 'send' ) );

		$params = new \Fastuc\Input\Http( 'GET' );

		$controller = new Base;		
		$controller->setHttpResponse( $response );
		$controller->doGet( $params );

		$this->assertEquals( 405, $response->getStatusCode() );
		$this->assertEquals( 'Method Not Allowed', $response->getBody() );
	}

	public function testHttpErrorCodes()
	{
		$mockResponse = $this->getMock( '\Fastuc\Http\Response', array( 'send' ) );

		$controller = new Base;
		$controller->setHttpResponse( $mockResponse );
		$controller->sendError( 404 );

		$this->assertEquals( 404, $mockResponse->getStatusCode() );
		$this->assertEquals( 'Not Found', $mockResponse->getBody() );
	}
}

