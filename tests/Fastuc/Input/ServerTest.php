<?hh // strict
namespace Fastuc\Input;

class ServerTest extends \PHPUnit_Framework_TestCase
{
	public function testRefererDoesNotExist()
	{
		$inputServer = new \Fastuc\Input\Server;
		$this->assertFalse( $inputServer->hasHttpReferer() );
	}
}

