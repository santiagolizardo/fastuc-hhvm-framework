<?hh // strict
namespace Fastuc\Html\Field;

class RadiosTest extends \PHPUnit_Framework_TestCase
{
	public function testAddRadio()
	{
		$field = new Radios( 'radios' );
		$field->addRadio( 'value', 'label' );
		$this->assertEquals( '<input id="radios" type="radio" name="radios" value="value" /> <label for="">label</label>', $field->__toString() );
	}
}

