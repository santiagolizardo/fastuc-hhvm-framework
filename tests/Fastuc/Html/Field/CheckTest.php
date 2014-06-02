<?hh // strict
namespace Fastuc\Html\Field;

class CheckTest extends \PHPUnit_Framework_TestCase
{
	public function testChecking()
	{
		$field = new Check( 'accept' );
		$this->assertFalse( $field->isChecked() );

		$field->setChecked( true );
		$this->assertTrue( $field->isChecked() );
		
		$field->setChecked( false );
		$this->assertFalse( $field->isChecked() );
	}
}

