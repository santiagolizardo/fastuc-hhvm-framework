<?hh // strict
namespace Fastuc\I18n;

class TranslatorTest extends \PHPUnit_Framework_TestCase
{
	public function testFileLoading()
	{
		$this->setExpectedException( '\Fastuc\I18n\Exception', 'Translation file does not exist: messages.mo' );
		$translator = new Translator;
		$translator->loadFile( 'messages.mo' );
	}
}

