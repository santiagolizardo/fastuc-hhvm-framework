<?hh // strict
namespace Fastuc\Html\Field;

class Submit extends \Fastuc\Html\Field
{
	public function __construct( $value = 'Submit' )
	{
		$this->value = $value;
	}

	public function __toString()
	{
		$html = sprintf( '<input type="submit" value="%s"', $this->value );
		if( null !== $this->class )
			$html .= sprintf( ' class="%s"', $this->class );
		$html .= ' />';
		return $html;
	}
}

