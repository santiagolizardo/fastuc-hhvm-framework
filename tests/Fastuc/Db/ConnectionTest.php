<?hh // strict
namespace Fastuc\Db;

class ConnectionTest extends \PHPUnit_Framework_TestCase
{
	public function testExceptionOnError()
	{
		$this->setExpectedException( '\Fastuc\Db\Exception', 'Access denied for user' );

		new Connection( 'localhost', 'wronguser', 'wrongpass', 'wrongname' );
	}

	public function testAssignedCharacterSet()
	{
		$db = new Connection( 'localhost', 'root', '', 'fastuc_testdb' );
		$this->assertEquals( 'utf8', $db->character_set_name() );
	}
}

