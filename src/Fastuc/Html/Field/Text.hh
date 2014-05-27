<?hh // strict
namespace Fastuc\Html\Field;

class Text extends \Fastuc\Html\InputField
{
	public function __construct( $name, $value = null )
	{
		parent::__construct( 'text', $name, $value );
	}
}

