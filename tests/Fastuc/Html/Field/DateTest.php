<?hh // strict
namespace Fastuc\Html\Field;

class DateTest extends \PHPUnit_Framework_TestCase
{
	public function testDefaults()
	{
		$field = new Date( 'birthday' );
		$this->assertFalse( $field->isRequired() );
		$this->assertFalse( $field->isAutofocus() );
		$this->assertNull( $field->getValue() );
	}
}

