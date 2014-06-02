<?hh // strict
namespace Fastuc\Web;

class DispatcherTest extends \PHPUnit_Framework_TestCase
{
	public function testDefaults()
	{
		$dispatcher = new Dispatcher;
		
		$this->assertEmpty( $dispatcher->getRoutes() );
		$this->assertEquals( '', $dispatcher->getBaseControllerNs() );
		$this->assertEquals( '', $dispatcher->getBaseControllerPath() );
	}
}

