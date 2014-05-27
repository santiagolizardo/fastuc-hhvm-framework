<?hh // strict
namespace Fastuc\Fs;

class FileTest extends \PHPUnit_Framework_TestCase
{
	public function testInitialization()
	{
		$file = new File( __FILE__ );
		$this->assertInstanceOf( '\SplFileInfo', $file );
		$this->assertEquals( 'FileTest.php', $file->getFilename() );
		$this->assertEquals( __FILE__, $file->getPathname() );
		$this->assertTrue( $file->exists() );
	}

	public function testPutGetContent()
	{
		$fileName = tempnam( __DIR__, 'test' );

		$file = new File( $fileName );

		$this->assertTrue( $file->exists() );
		$this->assertEquals( '', $file->getContents() );

		$this->assertTrue( $file->isWritable() );
		$file->putContents( 'testing' );
		$this->assertEquals( 'testing', $file->getContents() );

		$file->delete();
		$this->assertFalse( $file->exists() );
	}

	/**
	 * @expectedException Exception
	 * @expectedExceptionMessage File could not be deleted: i-dont-exist.txt
	 */
	public function testMissingFile()
	{
		$file = new File( 'i-dont-exist.txt' );
		$this->assertFalse( $file->exists() );
		$file->delete();
	}
}

