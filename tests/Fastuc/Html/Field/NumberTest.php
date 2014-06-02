<?hh // strict
namespace Fastuc\Html\Field;

class NumberTest extends \PHPUnit_Framework_TestCase
{
	public function testBasicSetterGetter()
	{
		$field = new Number( 'price' );
		$this->assertEquals( 'any', $field->getStep() );
		$this->assertEquals( '', $field->getValue() );
		$this->assertFalse( $field->isRequired() );

		$field->setValue( 0.5 );
		$this->assertEquals( 0.5, $field->getValue() );
	}
}

