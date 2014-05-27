<?hh // strict
namespace Fastuc\Input;

class FileTest extends \PHPUnit_Framework_TestCase
{
	/**
	 * @expectedException \Fastuc\Input\Exception
	 * @expectedExceptionMessage Invalid file name: image
	 */
	public function testWrongInitialization()
	{
		$name = 'image';
		new File( $name );
	}

	public function testInitialization()
	{
		$_FILES = array(
			'image' => array(
				'type' => 'image/png'
			)
		);

		$name = 'image';
		$input = new File( $name );
		$this->assertEquals( 'image/png', $input->getContentType() );
	}
}

