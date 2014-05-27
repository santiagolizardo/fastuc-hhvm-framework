<?hh // strict
namespace Fastuc\Html;

class FormTest extends \PHPUnit_Framework_TestCase
{
	public function testInitialization()
	{
		$form = new Form;
		$form->addField( new Field\Hidden( 'foobar' ) );
		
		$this->assertEquals( 'post', $form->getMethod() );
		$this->assertEquals( '', $form->getAction() );
		$this->assertNull( $form->getEncType() );
	}

	public function testMethodAssignment()
	{
		$form = new Form;
		$this->assertEquals( 'post', $form->getMethod() );

		$form->setMethod( 'get' );
		$this->assertEquals( 'get', $form->getMethod() );

		$form->setMethod( 'head' );
		$this->assertEquals( 'get', $form->getMethod() );
	}

	public function testHtmlOutput()
	{
		$form = new Form;

		$htmlForm = strval( $form );
		$this->assertNotContains( 'enctype="multipart/form-data"', $htmlForm );
		$this->assertContains( '<form', $htmlForm );
		
		$form->setEncType( 'multipart/form-data' );
		$htmlForm = strval( $form );
		$this->assertContains( 'enctype="multipart/form-data"', $htmlForm );

	}
}
