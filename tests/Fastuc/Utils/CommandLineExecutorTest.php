<?hh // strict
namespace Fastuc\Utils;

class CommandLineExecutorTest extends \PHPUnit_Framework_TestCase
{
	public function testRun()
	{
		$executor = new CommandLineExecutor( 'uname' );
		$executor->addArgument( '--all' );
		$executor->run();

		$this->assertEquals( 0, $executor->getExitCode() );
		$this->assertContains( 'Linux', $executor->getOutput() );
	}
}

