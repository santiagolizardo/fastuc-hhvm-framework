<?hh // strict
namespace Fastuc\Html\Field;

class PasswordTest extends \PHPUnit_Framework_TestCase
{
	public function testHtmlOutput()
	{
		$field = new Password( 'secret' );
		$this->assertContains( 'type="password"', $field->__toString() );
	}
}

