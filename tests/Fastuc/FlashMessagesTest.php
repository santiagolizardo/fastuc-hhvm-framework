<?hh // strict
namespace Fastuc;

class FlashMessagesTest extends \PHPUnit_Framework_TestCase
{
	public function testAddingMessages()
	{
		$fm = new \Fastuc\FlashMessages;
		$this->assertEquals( 0, count( $fm->getMessages() ) );

		$fm->addMessage( 'Your message has been received' );
		$this->assertEquals( 1, count( $fm->getMessages() ) );
	}
}
