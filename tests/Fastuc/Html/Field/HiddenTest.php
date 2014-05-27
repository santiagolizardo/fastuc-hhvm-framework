<?hh // strict
namespace Fastuc\Html\Field;

class HiddenTest extends \PHPUnit_Framework_TestCase
{
	public function testValue()
	{
		$field = new Hidden( 'id' );
		$this->assertEquals( '', $field->getValue() );

		$field->setValue( 5 );
		$this->assertEquals( 5, $field->getValue() );
	}
}

