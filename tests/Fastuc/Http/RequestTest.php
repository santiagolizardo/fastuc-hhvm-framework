<?hh // strict
namespace Fastuc\Http;

class RequestTest extends \PHPUnit_Framework_TestCase
{
	public function testRequestMethodRetrieval()
	{
		$_SERVER['REQUEST_METHOD'] = 'POST';

		$request = Request::createFromCurrentRequest();
		$this->assertEquals( 'POST', $request->getMethod() );
	}

	public function testAcceptLanguageHeader()
	{
		$request = new Request;

		$this->assertNull( $request->getAcceptLanguage() );
		$this->assertEquals( array(), $request->getAcceptLanguage( $asArray = true ) );

		$_SERVER['HTTP_ACCEPT_LANGUAGE'] = 'ca,es,en';

		$request = new Request;
		$this->assertEquals( 'ca,es,en', $request->getAcceptLanguage() );
		$this->assertEquals( array( 'ca', 'es', 'en' ), $request->getAcceptLanguage( $asArray = true ) );
	}
}

