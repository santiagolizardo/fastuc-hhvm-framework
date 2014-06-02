<?hh // strict
namespace Fastuc\Html\Field;

class RadioTest extends \PHPUnit_Framework_TestCase
{
	public function testToString()
	{
		$field = new Radio( 'radio' );
	        $field->setValue( 'value' );
        	$field->setLabel( 'label' );
		$this->assertEquals( '<input id="radio" type="radio" name="radio" value="value" /> <label for="">label</label>', $field->__toString() );
	}
}

