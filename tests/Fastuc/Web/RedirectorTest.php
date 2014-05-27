<?hh
namespace Fastuc\Web;

class RedirectorTest extends \PHPUnit_Framework_TestCase
{
	public function setUp()
	{
		parent::setUp();

		$_SERVER['REQUEST_URI'] = '/foo/bar';
	}

	public function tearDown()
	{
		unset( $_SERVER['REQUEST_URI'] );

		parent::tearDown();
	}

	public function testDefaults()
	{
		$redirector = new Redirector;
		$this->assertEquals( '/foo/bar', $redirector->getRequestPath() );
		$this->assertEquals( '', $redirector->getContextPath() );

		$redirector = new Redirector( '/foo' );
		$this->assertEquals( '/bar', $redirector->getRequestPath() );
		$this->assertEquals( '/foo', $redirector->getContextPath() );
	}

	public function testGoToUrl()
	{
		$redirector = $this->getMock( '\Fastuc\Web\Redirector', array( 'sendHeader' ) );
		$redirector->expects( $this->at( 0 ) )
			->method( 'sendHeader' )
			->with( 'HTTP/1.1 301 Moved Permanently' );
		$redirector->expects( $this->at( 1 ) )
			->method( 'sendHeader' )
			->with( 'Location: http://www.php.net' );
		$redirector->setExitAfterRedirection( false );
		$redirector->goToUrl( 'http://www.php.net', true );
	}
	
	public function testGoToReferer()
	{
		$redirector = $this->getMock( '\Fastuc\Web\Redirector', array( 'sendHeader' ) );
		$redirector->expects( $this->once() )
			->method( 'sendHeader' )
			->with( 'Location: /' );
		$redirector->setExitAfterRedirection( false );
		$redirector->goToReferer();
	}

	public function testGoToRefererWhenIsPresent()
	{
		$_SERVER['HTTP_HOST'] = 'www.google.es';
		$referalUrl = $_SERVER['HTTP_REFERER'] = 'http://www.google.es/?q=foobar';

		$redirector = $this->getMock( '\Fastuc\Web\Redirector', array( 'sendHeader' ) );
		$redirector->expects( $this->once() )
			->method( 'sendHeader' )
			->with( 'Location: ' . $referalUrl );
		$redirector->setExitAfterRedirection( false );
		$redirector->goToReferer();
	}
}

