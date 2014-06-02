<?hh // strict
namespace Fastuc\Exception;

class MissingExtensionTest extends \PHPUnit_Framework_TestCase
{
	public function testExceptionMessage()
	{
		$exception = new MissingExtension( 'foobar' );
		$this->assertInstanceOf( '\Exception', $exception );
		$this->assertEquals( 'The extension "foobar" is not installed', $exception->getMessage() );
	}
}

