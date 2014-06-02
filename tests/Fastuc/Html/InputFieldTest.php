<?hh // strict
namespace Fastuc\Html;

class InputFieldTest extends \PHPUnit_Framework_TestCase
{
	public function testFluentInterface()
	{
		$field = new InputField( 'text', 'foo' );
		$this->assertSame( $field, $field->setValue( 'bar' ) );

		$field->setRequired( true )->setClass( 'input input-large' );
		$this->assertEquals( 'input input-large', $field->getClass() );

		$this->assertEquals( 'text', $field->getType() );

		$this->assertFalse( $field->isReadonly() );
		$this->assertFalse( $field->isDisabled() );

		$field->setReadonly( true )->setDisabled( true );
		$this->assertTrue( $field->isReadonly() );
		$this->assertTrue( $field->isDisabled() );

		$field->setReadonly( false )->setDisabled( false );
		$this->assertFalse( $field->isReadonly() );
		$this->assertFalse( $field->isDisabled() );
	}
}

