<?hh // strict
namespace Fastuc\Html;

class FieldsTest extends \PHPUnit_Framework_TestCase
{
	public function testAddition()
	{
		$fields = new Fields;
		$this->assertEmpty( $fields->getFields() );

		$fieldControl = new Field\Text( 'name' );
		$fields->addField( $fieldControl, 'Name' );
		$this->assertEquals( 1, count( $fields->getFields() ) );
		$this->assertSame( $fields->getField( 0 ), $fieldControl );

		$fields->clearFields();
		$this->assertEmpty( $fields->getFields() );
	}
}

