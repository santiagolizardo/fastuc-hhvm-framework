<?hh // strict
namespace Fastuc\Config;

class FileTest extends \PHPUnit_Framework_TestCase
{
	public function testNameAssignment()
	{
		$file = new File;
		$this->assertNull( $file->getName() );

		$file = new File( 'email' );
		$this->assertEquals( 'email', $file->getName() );

		$file->setName( 'routes' );
		$this->assertEquals( 'routes', $file->getName() );
	}

	/**
	 * @expectedException Exception
	 * @expectedExceptionMessage Configuration file not found:
	 */
	public function testValueRetrievalFail()
	{
		$file = new File( 'abc' );
		$this->assertFalse( $file->exists() );
		$file->getValue();
	}

	public function testValueRetrieval()
	{
		$file = new File( 'names' );
		$file->setBasePath( __DIR__ );
		$this->assertEquals( __DIR__, $file->getBasePath() );
		$this->assertContains( 'Santi', $file->getValue() );
	}
}

